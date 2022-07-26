#include <cgmuduo/TcpServer.h>
#include <cgmuduo/Logger.h>
#include <cgmuduo/Buffer.h>

#include <string>

#include "echoServer.h"

EchoServer::EchoServer(EventLoop* loop, const InetAddress& listenAddr) 
    : server_(loop, listenAddr, "EchoServer"){
        server_.setConnectionCallback(
            std::bind(&EchoServer::onConnection, this, std::placeholders::_1)
        );
        server_.setMessageCallback(
            std::bind(&EchoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
        );

}

void EchoServer::start() {
    server_.start();
}

void EchoServer::onConnection(const TcpConnectionPtr& conn) {
    if(conn->connected()) {
        LOG_INFO("connection up : %s", conn->peerAddr().toIpPort().c_str());
    }
    else {
        LOG_INFO("connection down : %s", conn->peerAddr().toIpPort().c_str());
    }
}
    
void EchoServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time) {
    std::string msg = buf->retrieveAllAsString();
    LOG_INFO("%s echo %d bytes, data received at %s", conn->name(), msg.size(), time.toString());
    conn->send(msg);
    conn->shutdown();
}