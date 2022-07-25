
#include "Socket.h"
#include "Logger.h"
#include "InetAddress.h"

#include <sys/socket.h>
#include <sys/types.h>  
#include <unistd.h>
#include <netinet/tcp.h>
#include <strings.h>

Socket::Socket(int sockfd) : sockfd_(sockfd) {

}
Socket::~Socket() {
    ::close(sockfd_);
}

// 绑定地址
void Socket::bindAddress(const InetAddress &localaddr) {
    if( 0 != ::bind(sockfd_, (sockaddr*)localaddr.getSockAddr(), sizeof(sockaddr_in))) {
        LOG_FATAL("bind() sockfd:%d fail \n", sockfd_);
    }
}

// 监听
void Socket::listen() {
    if(0 != ::listen(sockfd_, 1024)) {
        LOG_FATAL("listen() sockfd:%d fail \n", sockfd_);
    }
}

// 等待接收客户端，并返回连接
int Socket::accept(InetAddress *peeraddr) {
    sockaddr_in addr;
    socklen_t len = sizeof addr;
    bzero(&addr, sizeof addr);
   int connfd = ::accept4(sockfd_, (sockaddr*)&addr, &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if(connfd >= 0) {
        peeraddr->setSockAddr(addr);
    }
    return connfd;
}

// 关闭写端
void Socket::shutdownWrite() {
    if(::shutdown(sockfd_, SHUT_WR) < 0) {
        LOG_ERROR("shutdownWrite error\n");
    }
}

// TCP_NODELAY 用来控制是否开启Nagle算法
void Socket::setTcpNoDelay(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof optval);
}

//  SO_REUSEADDR 地址复用
void Socket::setReuseAddr(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
}


// SO_REUSEPORT 多个socket绑定在同一个监听端口，然后让内核给你自动做负载均衡，将请求平均地让多个线程进行处理。
void Socket::setReusePort(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof optval);
}

// SO_KEEPALIVE 用于开启或者关闭保活探测
void Socket::setKeepAlive(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof optval);
}