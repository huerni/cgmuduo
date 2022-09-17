#include <cgmuduo/EventLoop.h>
#include <cgmuduo/TcpServer.h>

void onConnection(const TcpConnectionPtr& conn) {
    if(conn->connected()) {
        std::cout<<1;
        conn->shutdown();
    }
}

int main(){
    EventLoop loop;
    TcpServer server(&loop, InetAddress(1079), "Finger");
    server.setConnectionCallback(onConnection);
    server.start();
    loop.loop();

    return 0;
}