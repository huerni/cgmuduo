
#include "discard.h"

DiscardServer::DiscardServer(EventLoop* loop, const InetAddress& listenAddr)
    : server_(loop, listenAddr, "DiscardServer") {

    server_.setConnectionCallback(
        std::bind(&DiscardServer::onConnection, this, std::placeholders::_1)
    );
    server_.setMessageCallback(
        std::bind(&DiscardServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
    );
}

void DiscardServer::start() {
    server_.start();
}

void DiscardServer::onConnection(const TcpConnectionPtr& conn) {
    LOG_INFO("ChargenServer - %s -> %s is %s", 
            conn->peerAddr().toIpPort().c_str(), 
            conn->localAddr().toIpPort().c_str(), 
            (conn->connected() ? "UP" : "DOWN")
    );
}

void DiscardServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time) {
    string msg(buf->retrieveAllAsString());

    LOG_INFO("%s discards %d bytes received at %s", conn->name().c_str(), msg.size(), time.toString().c_str());
}

