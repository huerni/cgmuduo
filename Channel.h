#pragma once

#include "noncopyable.h"
#include <functional>
#include "Timestamp.h"
#include <memory>

class EventLoop;

/**
 * 通道类，封装了一个socketfd及其event，存在一系列回调函数，绑定了poller返回的具体事件
 * 
*/
class Channel : noncopyable{
public:
    // 回调函数
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop* loop, int fd);
    ~Channel();
    
    // 处理事件的接口
    void HandleEvent(Timestamp receiveTime);

    // 设置回调函数，有读，写，关闭，错误事件
    void setReadCallback(ReadEventCallback cb) { readCallback_ = std::move(cb); }
    void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); }
    void setCloseCallback(EventCallback cb) { closeCallback_ = std::move(cb); }
    void setErrorCallback(EventCallback cb) { errorCallback_ = std::move(cb); }

    // 绑定指针，将弱指针转为共享指针
    void tie(const std::shared_ptr<void>& );

    int fd() const { return fd_; }
    int events() const { return events_; }
    int set_revents(int revt) { revents_ = revt; }
    

    // 更新fd感兴趣的事件events
    void enableReading() { events_ |= KReadEvent; update(); }
    void disableReading() { events_ &= ~KReadEvent; update(); }
    void enableWriting() { events_ |= KWriteEvent; update(); }
    void disableWriting() { events_ &= ~KWriteEvent; update(); }
    void disableAll() { events_ = KNoneEvent; update(); }

    bool isNoneEvent() const { return events_ == KNoneEvent; }
    bool isWriteEvent() const { return events_ & KWriteEvent; }
    bool inReadEvent() const { return events_ & KReadEvent; }

    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }

    EventLoop* ownerLoop() { return loop_; }
    void remove();
    
private:
    // 通知所属的eventloop更新events
    void update();
    // 根据事件event类型进行相应的处理
    void handleEventWithGuard(Timestamp receiveTime);

    // 三种事件
    static const int KNoneEvent;
    static const int KReadEvent;
    static const int KWriteEvent;

    EventLoop *loop_;
    const int fd_;
    int events_;
    int revents_;
    int index_;

    std::weak_ptr<void> tie_;
    bool tied_;

    // 四种回调函数
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};


