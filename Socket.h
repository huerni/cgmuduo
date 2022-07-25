#pragma once

#include "noncopyable.h"

class InetAddress;

/**
 * socket封装
*/
class Socket : noncopyable{
public:
    explicit Socket(int sockfd);
    ~Socket();

    int fd() const { return sockfd_; }
    void bindAddress(const InetAddress &localaddr);
    void listen();
    int accept(InetAddress *peeraddr);
    void shutdownWrite();

    void setTcpNoDelay(bool on);
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void setKeepAlive(bool on); 
private:
    const int sockfd_;
};