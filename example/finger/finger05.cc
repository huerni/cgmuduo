#include <cgmuduo/EventLoop.h>
#include <cgmuduo/TcpServer.h>
#include <cgmuduo/Logger.h>
#include <cgmuduo/Buffer.h>
#include <cgmuduo/Timestamp.h>

#include <string>


void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime) {
    if(buf->findCRLF()) {
        conn->send("No such user\r\n");
        conn->shutdown();
    }
}

int main() {
    EventLoop loop;
    TcpServer server(&loop, InetAddress(1079), "finger");
    server.setMessageCallback(onMessage);
    server.start();
    loop.loop();

    return 0;
}