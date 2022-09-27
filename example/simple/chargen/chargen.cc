#include "chargen.h"
#include <cgmuduo/Logger.h>

#include <functional>
#include <unistd.h>

ChargenServer::ChargenServer(EventLoop* loop, const InetAddress& listenAddr, bool print) 
                :server_(loop, listenAddr, "ChargenServer")
                ,transferred_(0)
                ,startTime_(Timestamp::now()) {
    
    server_.setConnectionCallback(
      std::bind(&ChargenServer::onConnection, this, std::placeholders::_1)  
    );

    server_.setMessageCallback(
        std::bind(&ChargenServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
    );

    server_.setWriteCompleteCallback(
        std::bind(&ChargenServer::onWriteComplete, this, std::placeholders::_1)
    );

    if(print) {
       // loop->runEvery(3.0, std::bind(&ChargenServer::printThroughput, this));
    }

    std::string line;
    for (int i = 33; i<127; ++i) {
        line.push_back(char(i));
    }

    line += line;

    for(size_t i = 0; i<127-33; ++i) {
        message_ += line.substr(i, 72) + "\r\n";
    }
}

void ChargenServer::start() {
    server_.start();
}

void ChargenServer::onConnection(const TcpConnectionPtr& conn) {
    LOG_INFO("ChargenServer - %s -> %s is %s", conn->peerAddr().toIpPort().c_str(), conn->localAddr().toIpPort().c_str(), (conn->connected() ? "UP" : "DOWN"));

    if(conn->connected()) {
        conn->setTcpNoDelay(true);
        conn->send(message_);
    }
}

void ChargenServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time) {
    std::string msg(buf->retrieveAllAsString());
    LOG_INFO("%s discards %d bytes received at %s", conn->name().c_str(), msg.size(), time.toString().c_str());
}

void ChargenServer::onWriteComplete(const TcpConnectionPtr& conn) {
    transferred_ += message_.size();
    conn->send(message_);
}

void ChargenServer::printThroughput() {
    Timestamp endTime = Timestamp::now();
    double time = timeDifference(endTime, startTime_);
    printf("%4.3f MiB/s\n", static_cast<double>(transferred_)/time/1024/1024);
    transferred_ = 0;
    startTime_ = endTime;
}