#pragma once

#include <cgmuduo/TcpServer.h>

#include <string>

class ChargenServer{
public:
    ChargenServer(EventLoop* loop, const InetAddress& listenAddr, bool print = false);

    void start();
    
private:
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time);
    void onWriteComplete(const TcpConnectionPtr& conn);
    void printThroughput();

    TcpServer server_;
    std::string message_;
    int64_t transferred_;
    Timestamp startTime_;
};