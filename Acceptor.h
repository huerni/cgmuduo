#pragma once

#include "noncopyable.h"
#include "Socket.h"
#include "Channel.h"

#include <functional>

class EventLoop;

class Acceptor : noncopyable {
public:
    using newConnectionCallback = std::function<void(int sockfd, const InetAddress&)>;

    Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport);
    ~Acceptor();

    void setNewConnectionCallback(const newConnectionCallback &cb) {
        newConnectionCallback_ = cb;
    }

    bool listenning() const { return listenning_; }
    void listen();
private:
    void handleRead();

    EventLoop *loop_;
    Socket acceptSocket_;
    Channel acceptChannel_;
    newConnectionCallback newConnectionCallback_;
    bool listenning_;
};