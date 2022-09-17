#include <cgmuduo/EventLoop.h>
#include <cgmuduo/TcpServer.h>
#include <cgmuduo/Logger.h>

void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime) {
    if(buf->findCRLF()) {
        conn->shutdown();
    }
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
    server.start();
    loop.loop();
}