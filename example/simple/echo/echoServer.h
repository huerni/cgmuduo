#pragma once

#include <cgmuduo/TcpServer.h>
#include <cgmuduo/Logger.h>
#include <string>
#include <functional>
using std::string;

class EchoServer{
public:
    EchoServer(EventLoop* loop, const InetAddress& listenAddr);

    void start();

private:
    void onConnection(const TcpConnectionPtr& conn);

    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time);

    TcpServer server_;
};