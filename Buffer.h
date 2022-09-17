#pragma once

#include <vector>
#include <string>
#include <algorithm>

class Buffer{
public:
    static const size_t kCheapPrepend = 8;
    static const size_t kInitalSize = 1024;

    explicit Buffer(size_t initialSize = kInitalSize) : buffer_(kCheapPrepend+initialSize)
            , readerIndex_(kCheapPrepend)
            , writerIndex_(kCheapPrepend) 
    {}

    // 可读数据大小，即缓存区内已存数据大小
    size_t readableBytes() const {
        return writerIndex_ - readerIndex_;
    }

    // 可写数据大小，即缓冲区剩余空间
    size_t writableBytes() const {
         return buffer_.size() - writerIndex_;
    }

    // 可读位置之前的大小(包含预留空间+已读空间)
    size_t prependableBytes() const {
        return readerIndex_;
    }

    // 可读数据起始地址
    const char* peek() const {
        return begin() + readerIndex_;
    }

    // 读取后调整读写指针
    void retrieve(size_t len) {
        if(len < readableBytes()) {
            readerIndex_ += len;
        }
        else {
            retrieveAll();
        }
    }

    // 将读写指针归为初始
    void retrieveAll() {
        readerIndex_ = writerIndex_ = kCheapPrepend;
    }

    // 将缓存区内所有数据转为string
    std::string retrieveAllAsString() {
        return retrieveAsString(readableBytes());
    }

    // 将指定长度可读数据转为string
    std::string retrieveAsString(size_t len) {
        std::string result(peek(), len);
        retrieve(len);
        return result;
    }

    // 确保是否有足够空间可写
    void ensureWriteableBytes(size_t len) {
        if(writableBytes() < len) {
            makeSpace(len);
        }
    }

    // 将len长度data写入缓存区
    void append(const char* data, size_t len) {
        ensureWriteableBytes(len);
        std::copy(data, data+len, beginWrite());
        writerIndex_ += len;
    }

    char* beginWrite() {
        return begin() + writerIndex_;
    }

    const char* beginWrite() const {
        return begin() + writerIndex_;
    }

    const char* findCRLF() const {
        const char* crlf = std::search(peek(), beginWrite(), KCRLF, KCRLF+2);
        return crlf == beginWrite() ? NULL : crlf;
    }
    
    ssize_t readFd(int fd, int* saveErrno);

    ssize_t writeFd(int fd, int* saveErrno);

private:
    char* begin() {
        // 解开迭代器，取地址
        return &*buffer_.begin();
    }

    const char* begin() const {
        return &*buffer_.begin();
    }

    // 扩充空间
    void makeSpace(size_t len) {
        // 当可写空间+已读空间不足时，扩充vector长度
        // (因为可读位置每次读取是向后走的，这样前面会有一段不可用但空白区域，类似线性队列)
        if(writableBytes() + prependableBytes() < len + kCheapPrepend) {
            
            buffer_.resize(writerIndex_ + len);
        }
        // 否则不需要扩充，只要将可读数据向前移动即可。
        else {
            size_t readable = readableBytes();
            std::copy(begin() + readerIndex_, begin() + writerIndex_, begin() + kCheapPrepend);
            readerIndex_ = kCheapPrepend;
            writerIndex_ = readerIndex_ + readable;
        }
    }

    std::vector<char> buffer_;
    size_t readerIndex_;
    size_t writerIndex_;

    static const char KCRLF[];
};