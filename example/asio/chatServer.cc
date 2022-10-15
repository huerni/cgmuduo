
#include<cgmuduo/TcpServer.h>

#include "codec.h"
#include <set>
#include <functional>
#include <unistd.h>

class ChatServer : noncopyable {
public:
    using ConnectionList = std::set<TcpConnectionPtr>;

    ChatServer(EventLoop* loop, const InetAddress& listenAddr) 
        : loop_(loop)
        , server_(loop, listenAddr, "ChatServer")
        , codec_(std::bind(&ChatServer::onStringMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)) {

        server_.setConnectionCallback(
            std::bind(&ChatServer::onConnection, this, std::placeholders::_1)
        );

        server_.setMessageCallback(
            std::bind(&LengthHeaderCodec::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
        );
    }

    void start(){
        server_.start();
    }

private:
    void onConnection(TcpConnectionPtr& conn) {
        LOG_INFO("ChargenServer - %s -> %s is %s", conn->peerAddr().toIpPort().c_str(), conn->localAddr().toIpPort().c_str(), (conn->connected() ? "UP" : "DOWN"));
        if(conn->connected()) {
            connections_.insert(conn);
        }
        else {
            connections_.erase(conn);
        }
    }

    void onStringMessage(const TcpConnectionPtr&, const std::string& message, Timestame) {
        for(ConnectionList::iterator it = connections_begin(); it != connections_.end(); ++it) {
            codec_.send(get_pointer(*it), message);
        }
    }

    EventLoop *loop_;
    TcpServer server_;
    LengthHeaderCodec codec_;
    ConnectionList connections_;
};



int main(int argc, char* argv[]) {
    LOG_INFO("pid = %d", getpid());

    if(argc > 1) {
        EventLoop loop;
        uint16t port = static_cast<uint16t>(atoi(argv[1]));
        InetAddress serverAddr(port);
        ChatServer server(&loop, serverAddr);
        server.start();
        loop.loop();
    }
    else {
        print("Usage: %s prot\n", argv[0]);
    }
}