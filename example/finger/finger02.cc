#include <cgmuduo/EventLoop.h>
#include <cgmuduo/TcpServer.h>

int main() {
    EventLoop loop;
    TcpServer server(&loop, InetAddress(2020), "Finger");
    server.start();
    loop.loop();
}