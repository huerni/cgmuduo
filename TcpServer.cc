#include "TcpServer.h"
#include "EventLoop.h"
#include "Logger.h"
#include "InetAddress.h"
#include "Acceptor.h"
#include "EventLoopThreadPool.h"
#include "TcpConnection.h"

#include <strings.h>
#include <functional>

static EventLoop* CheckLoopNotNull(EventLoop* loop) {
    if(loop == nullptr) {
        LOG_FATAL("[%s:%s:%d] mainLoop is null! \n", __FILE__, __FUNCTION__, __LINE__);
    }
    return loop;
}

void defaultConnectionCallback(const TcpConnectionPtr& conn) {
    std::string isConnected = ((conn->connected()) ? "UP" : "DOWN");
    LOG_INFO("%s -> %s is %s \n", conn->localAddr().toIpPort().c_str(), conn->peerAddr().toIpPort().c_str(), isConnected.c_str());
}

void defaultMessageCallback(const TcpConnectionPtr&, Buffer* buf, Timestamp) {
    buf->retrieveAll();
}

TcpServer::TcpServer(EventLoop* loop, 
                    const InetAddress &listenAddr, 
                    const std::string &nameArg, 
                    Option option)
                : loop_(CheckLoopNotNull(loop))
                , ipPort_(listenAddr.toIpPort())
                , name_(nameArg)
                , acceptor_(new Acceptor(loop, listenAddr, option == kReusePort))
                , threadPool_(new EventLoopThreadPool(loop, name_))
                , connectionCallback_(defaultConnectionCallback)
                , messageCallback_(defaultMessageCallback)
                , nextConnId_(1)
                , started_(0) 
{
    acceptor_->setNewConnectionCallback(std::bind(&TcpServer::newConnection, this, 
        std::placeholders::_1, std::placeholders::_2));
}

TcpServer::~TcpServer() {
    for(auto& item : connections_) {
        TcpConnectionPtr conn(item.second); //局部智能指针，出作用域后自动释放对象资源
        item.second.reset();
        conn->getLoop()->runInLoop(
            std::bind(&TcpConnection::connectDestroyed, conn)
        );
    }
}


void TcpServer::setThreadNum(int numThreads) {
    threadPool_->setThreadNum(numThreads);
}

void TcpServer::start() {
    if(started_++ == 0) {
        threadPool_->start(threadInitCallback_);
        loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get()));
    }
}

// 有新连接，使用一个subloop创立connection处理
void TcpServer::newConnection(int sockfd, const InetAddress &peerAddr) {
    EventLoop *ioLoop = threadPool_->getNextLoop();
    char buf[64] = {0};
    snprintf(buf, sizeof buf, "-%s#%d", ipPort_.c_str(), nextConnId_);
    ++nextConnId_;
    std::string connName = name_ + buf;

    LOG_INFO("TcpServer::newConnection [%s] - new connection [%s] from %s \n", 
    name_.c_str(), connName.c_str(), peerAddr.toIpPort().c_str());

    sockaddr_in local;
    ::bzero(&local, sizeof local);
    socklen_t addrlen = sizeof local;
    if(::getsockname(sockfd, (sockaddr*)&local, &addrlen) < 0) {
        LOG_ERROR("sockets::getLocalAddr");
    }
    InetAddress localAddr(local);

    TcpConnectionPtr conn(new TcpConnection(
                            ioLoop,
                            connName,
                            sockfd,
                            localAddr,
                            peerAddr));

    connections_[connName] = conn;
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);

    conn->setCloseCallback(
        std::bind(&TcpServer::removeConnection, this, std::placeholders::_1)
    );

    ioLoop->runInLoop(std::bind(&TcpConnection::connectEstableished, conn));
}

void TcpServer::removeConnection(const TcpConnectionPtr &conn) {
    loop_->runInLoop(
        std::bind(&TcpServer::removeConnectionInLoop, this, conn)
    );
}

void TcpServer::removeConnectionInLoop(const TcpConnectionPtr &conn) {
    LOG_INFO("TcpServer::removeConnectionInLoop [%s] - connection %s \n", name_.c_str(), conn->name().c_str());

    connections_.erase(conn->name());
    EventLoop *ioLoop = conn->getLoop();
    ioLoop->queueInLoop(
        std::bind(&TcpConnection::connectDestroyed, conn)
    );
}