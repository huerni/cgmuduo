#include "Channel.h"
#include "EventLoop.h"
#include "Logger.h"

#include <sys/epoll.h>

const int Channel::KNoneEvent = 0;
const int Channel::KReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::KWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop* loop, int fd) 
    : loop_(loop), fd_(fd), events_(0), revents_(0), index_(-1), tied_(false) {

}

Channel::~Channel() {

}

// 当TcpConnection新连接创建的时候绑定
void Channel::tie(const std::shared_ptr<void>& obj) {
    tie_ = obj;
    tied_ = true;
}
 
// 当改变channel所表示的fd的events事件时，update负责在poller里面更改fd相应的事件epoll_ctl
// 为什么写在这里?  因为只有channel知道自己感兴趣的事件
void Channel::update() {
    loop_->updateChannel(this);
}

void Channel::remove() {
    loop_->removeChannel(this);
}

// fd得到poller通知以后，处理对应的事件
// 为什么由channel处理? 因为只有channel知道自己感兴趣的事件
void Channel::HandleEvent(Timestamp receiveTime) {
    if(tied_) {
        std::shared_ptr<void> guard = tie_.lock();
        if(guard) {
            handleEventWithGuard(receiveTime);
        }
    }
    else {
        handleEventWithGuard(receiveTime);
    }
}

// epoll下发通知channle具体事件，channel负责执行对应的回调
// epoll不感兴趣具体的channle事件，只有channel自己清楚自己要干什么，所以由channel调用回调
// 而回调由具体使用程序，即用户定义。
void Channel::handleEventWithGuard(Timestamp receiveTime) {

    if((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
        if(closeCallback_) {
            closeCallback_();
        }
    }

    if(revents_ & EPOLLERR) {
        if(errorCallback_) {
            errorCallback_();
        }
    }

    if(revents_ & (EPOLLIN | EPOLLPRI)) {
        if(readCallback_) {
            readCallback_(receiveTime);
        }
    }

    if(revents_ & EPOLLOUT) {
        if(writeCallback_) {
            writeCallback_();
        }
    }
}

