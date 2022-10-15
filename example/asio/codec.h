
#pragma once;

#include <cgmuduo/TcpConnection.h>
#include <cgmuduo/Timestamp.h>
#include <cgmuduo/Logger.h>

#include <string>

class LengthHeaderCodec : noncopyable {
public:
    using StringMessageCallback = std::function<void (const TcpConnectionPtr&, const std::string& message, Timestamp)>;

    explicit LengthHeaderCodec(const StringMessageCallback& cb)
        : messageCallback_(cb) {}

    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime) {
        while(buf->readableBytes() >= kHeaderLen) {
            const void* data = buf->peek();
            int32_t be32 = *static_cast<const int32_t*>(data);
            const int32_t len = be32toh(be32);
            if(len > 65536 || len < 0) {
                LOG_ERROR("Invalid length %d", len);
                conn->shutdown();
                break;
            }
            else if(buf->readableBytes() >= len + kHeaderLen) {
                buf->retrieve(kHeaderLen);
                std::string message(buf->peek(), len);
                messageCallback_(conn, message, receiveTime);
                buf->retrieve(len);
            }
            else {
                break;
            }
        }
    }

    void send(TcpConnection* conn, std::string& message) {
        Buffer buf;
        buf.append(message.c_str(), message.size());
        int32_t len = static_cast<int32_t>(message.size());
        int32_t be32 = htobe32(len);
        buf.prepend(&be32, sizeof be32);
        conn->send(&buf);
    }

private:
    StringMessageCallback messageCallback_;
    const static size_t kHeaderLen = sizeof(int32_t);
};