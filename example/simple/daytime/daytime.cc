
#include "daytime.h"

DaytimeServer::DaytimeServer(EventLoop* loop, const InetAddress& listenAddr)
    : server_(loop, listenAddr, "DaytimeServer") {

    server_.setConnectionCallback(
        std::bind(&DaytimeServer::onConnection, this, std::placeholders::_1)
    );
    server_.setMessageCallback(
        std::bind(&DaytimeServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
    );
}

void DaytimeServer::start() {
    server_.start();
}

void DaytimeServer::onConnection(const TcpConnectionPtr& conn) {
    LOG_INFO("ChargenServer - %s -> %s is %s", 
            conn->peerAddr().toIpPort().c_str(), 
            conn->localAddr().toIpPort().c_str(), 
            (conn->connected() ? "UP" : "DOWN")
    );
}

void DaytimeServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time) {
    LOG_INFO("dAYTIMEsERVER - %s -> %s is %s", conn->peerAddr().toIpPort().c_str(), conn->localAddr().toIpPort().c_str(), (conn->connected() ? "UP" : "DOWN"));
    if(conn->connected()) {
        conn->send(Timestamp::now().toString() + "\r\n");
        conn->shutdown();
    }
}

