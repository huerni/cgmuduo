#include <cgmuduo/TcpServer.h>
#include <cgmuduo/Logger.h>
#include <cgmuduo/Buffer.h>

#include <string>
#include <functional>

class EchoServer{
public:
    EchoServer(EventLoop* loop, const InetAddress &addr, const std::string &name) 
        :loop_(loop), server_(loop, addr, name) {
            server_.setConnectionCallback(
                std::bind(&EchoServer::onConnection, this, std::placeholders::_1)
            );
            server_.setMessageCallback(
                std::bind(&EchoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
            );

            server_.setThreadNum(3);
    }
    void start() {
        server_.start();
    }
private:
    // 连接建立和断开时调用
    void onConnection(const TcpConnectionPtr &conn) {
        if(conn->connected()) {
            LOG_INFO("connection up %s", conn->peerAddr().toIpPort().c_str());
        }
        else {
            LOG_INFO("connection down %s", conn->peerAddr().toIpPort().c_str());
        }
    }

    // 可读写时调用
    void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp time) {
        std::string msg = buf->retrieveAllAsString();
        conn->send(msg);
        conn->shutdown();
    }

    EventLoop *loop_;
    TcpServer server_;
};

int main(){
    EventLoop loop;
    InetAddress addr(8000);
    EchoServer server(&loop, addr, "echoServer");
    server.start();
    LOG_INFO("1");
    loop.loop();
    return 0;
}