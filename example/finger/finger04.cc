#include <cgmuduo/EventLoop.h>
#include <cgmuduo/TcpServer.h>
#include <cgmuduo/Logger.h>
#include <cgmuduo/Buffer.h>
#include <cgmuduo/Timestamp.h>

#include <string>


// FIXME:只接收一次消息就自动断开连接
void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime) {
    if(buf->findCRLF()) {
        std::string msg = buf->retrieveAllAsString();
        LOG_INFO("message: %s \n", msg.c_str());
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