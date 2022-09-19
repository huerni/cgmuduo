#include "TcpConnection.h"
#include "Logger.h"
#include "Socket.h"
#include "Channel.h"
#include "EventLoop.h"

#include <functional>
#include <errno.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <strings.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <string>
#include <unistd.h>

static EventLoop* CheckLoopNotNull(EventLoop* loop) {
    if(loop == nullptr) {
        LOG_FATAL("%s:%s:%d TcpConnection is null! \n", __FILE__, __FUNCTION__, __LINE__);
    }
    return loop;
}

TcpConnection::TcpConnection(EventLoop* loop, const std::string &name, int sockfd
        , const InetAddress& localAddr
        , const InetAddress& peerAddr) 
        : loop_(CheckLoopNotNull(loop))
        , name_(name)
        , state_(kConnecting)
        , reading_(true)
        , socket_(new Socket(sockfd))
        , channel_(new Channel(loop, sockfd))
        , localAddr_(localAddr)
        , peerAddr_(peerAddr)
        , highWaterMark_(64*1024*1024) {

    channel_->setReadCallback(std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
    channel_->setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    channel_->setCloseCallback(std::bind(&TcpConnection::handleClose, this));
    channel_->setErrorCallback(std::bind(&TcpConnection::handleError, this));

    LOG_INFO("TcpConnection::ctor[%s] at fd=%d\n", name_.c_str(), sockfd);
    socket_->setKeepAlive(true);
}

TcpConnection::~TcpConnection() {
    LOG_INFO("TcpConnection::dtor[%s] at fd=%d state=%d \n", name_.c_str(), channel_->fd(), (int)state_);
}

void TcpConnection::handleRead(Timestamp receiveTime) {
    int saveError = 0;
    // 从fd中读取
    int n = inputBuffer_.readFd(channel_->fd(), &saveError);
    if(n > 0) {
        messageCallback_(shared_from_this(), &inputBuffer_, receiveTime);
    }
    else if(n == 0) {
        handleClose();
    }
    else {
        errno = saveError;
        LOG_ERROR("TcpConnection::handleRead");
        handleError();
    }
}

void TcpConnection::handleWrite() {
    
    if(channel_->isWriteEvent()) {
        int saveError = 0;
        int n = outputBuffer_.writeFd(channel_->fd(), &saveError);
        if(n > 0) {
            outputBuffer_.retrieve(n);
            if(outputBuffer_.readableBytes() == 0) {
                channel_->disableWriting();
                if(writeCompleteCallback_) {
                    loop_->queueInLoop(
                        std::bind(writeCompleteCallback_, shared_from_this())
                    );
                }
            }
            if(state_ == kDisconnecting) {
                shutdownInLoop();
            }
        }
        else {
            LOG_ERROR("TcpConnection::handleWrite");
        }
    }
    else {
        LOG_ERROR("TcpConnection fd=%d is down, no more writing \n", channel_->fd());
    }
}

void TcpConnection::send(const std::string &buf) {
    if(state_ == kConnected) {
        if(loop_->isInLoopThread()) {
            sendInLoop(buf.c_str(), buf.size());
        }
        else {
            loop_->runInLoop(
                std::bind(&TcpConnection::sendInLoop, this, buf.c_str(), buf.size())
            );
        }
    }
}

void TcpConnection::sendInLoop(const void *message, size_t len) {
    ssize_t nwrote = 0;
    size_t remaining = len;
    bool faultError = false;

    // 判断连接状态
    if(state_ == kDisconnected) {
        LOG_ERROR("disconnected, give up writing!");
        return ;
    }

    // 第一次发送数据，且缓冲区没有待发送数据
    if(!channel_->isWriteEvent() && outputBuffer_.readableBytes() == 0) {
        nwrote = ::write(channel_->fd(), message, len);
        if(nwrote >= 0) {
            remaining = len - nwrote;
            // 一次性发送完成，调用写完成事件
            if(remaining == 0 && writeCompleteCallback_) {
                loop_->queueInLoop(
                    std::bind(writeCompleteCallback_, shared_from_this())
                );
            }
        }
        else {
            nwrote = 0;
            if(errno != EWOULDBLOCK) {
                LOG_ERROR("TcpConnection::sendInLoop");
                if(errno == EPIPE || errno == ECONNRESET) { //对方关闭管道或连接重置
                    faultError = true;
                }
            }
        }
    }

    // 还有剩余数据未发送，将剩余数据保存到输出buffer中，并给channel注册epollout事件
    // poller发现发送缓冲区有空间，通知对应的channel调用handlewrite事件
    if(!faultError && remaining > 0) { 
        size_t oldlen = outputBuffer_.readableBytes();
        if(oldlen + remaining >= highWaterMark_ && oldlen < highWaterMark_ && highWaterMarkCallback_) {
            loop_->queueInLoop(
                std::bind(highWaterMarkCallback_, shared_from_this(), oldlen+remaining)
            );
        }
        outputBuffer_.append((char*)message+nwrote, remaining);
        if(!channel_->isWriteEvent()) {
            channel_->enableWriting();
        }
    }

}

// 关闭写端
void TcpConnection::shutdown() {
    if(state_ == kConnected) {
        setState(kDisconnecting);
        loop_->runInLoop(
            std::bind(&TcpConnection::shutdownInLoop, this)
        );
    }
}

void TcpConnection::shutdownInLoop() {
    if(!channel_->isWriteEvent()) {

        socket_->shutdownWrite();
    }
}


// 连接建立
void TcpConnection::connectEstableished() {
    setState(kConnected);
    channel_->tie(shared_from_this()); // 绑定
    channel_->enableReading(); // 设置可读

    connectionCallback_(shared_from_this());
}

// 连接销毁 

void TcpConnection::connectDestroyed() {
    if(state_ == kConnected) {
        setState(kDisconnected);
        channel_->disableAll();
        connectionCallback_(shared_from_this());
    }
    
    channel_->remove();
}


void TcpConnection::handleClose() {
    LOG_INFO("fd=%d, state=%d \n", channel_->fd(), (int)state_);
    setState(kDisconnected);

    TcpConnectionPtr connPtr(shared_from_this());
    connectionCallback_(connPtr);
    closeCallback_(connPtr);
}

void TcpConnection::handleError() {
    int optval;
    socklen_t optlen = sizeof optval;
    int err = 0;
    if(::getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0) {
        err = errno;
    }
    else {
        err = optval;
    }
    LOG_ERROR("TcpConnection::handleError name:%s - SO_ERROR:%d \n", name_.c_str(), err);
}

