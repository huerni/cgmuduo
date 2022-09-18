#include <cgmuduo/EventLoop.h>
#include <cgmuduo/TcpServer.h>
#include <cgmuduo/Logger.h>

#include <string>
#include <functional>
#include <unistd.h>


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
    
    server.setMessageCallback(onMessage);
    server.setConnectionCallback(onConnection);
    server.start();
    loop.loop();

    return 0;
}