#include <cgmuduo/EventLoop.h>
#include <cgmuduo/TcpServer.h>
#include <cgmuduo/Logger.h>
#include <cgmuduo/Buffer.h>
#include <cgmuduo/Timestamp.h>

#include <string>


void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime) {
    LOG_INFO("connection up message");
}

void onConnection(const TcpConnectionPtr& conn) {
    if(conn->connected()) {
        LOG_INFO("connection up : %s", conn->peerAddr().toIpPort().c_str());
    }
    else {
        LOG_INFO("connection down : %s", conn->peerAddr().toIpPort().c_str());
    }
}

int main() {
    EventLoop loop;
    TcpServer server(&loop, InetAddress(1079), "finger");
    server.setConnectionCallback(onConnection);
    server.setMessageCallback(onMessage);
    server.start();
    loop.loop();

    return 0;
}