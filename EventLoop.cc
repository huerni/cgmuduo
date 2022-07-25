#include "EventLoop.h"
#include "Logger.h"
#include "Poller.h"
#include "Channel.h"

#include <sys/eventfd.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// 防止一个线程创建多个EventLoop
__thread EventLoop *t_loopInThisThread = nullptr;

// 默认Poller IO复用接口的超时时间
const int kPollTimeMs = 10000;

// 创建eventfd
int createEventfd() {
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if(evtfd < 0) {
        LOG_FATAL("eventfd error:%d \n", errno);
    }
    return evtfd;
}

EventLoop::EventLoop() 
    : looping_(false), quit_(false), callingPendingFunctors_(false)
    , threadId_(CurrentThread::tid())
    , poller_(Poller::newDefaultPoller(this))
    , wakeupFd_(createEventfd())
    , wakeupChannel_(new Channel(this, wakeupFd_)) {

    LOG_INFO(" [%s:%s:%d] EventLoop created %p in thread %d \n", __FILE__, __FUNCTION__, __LINE__, this, threadId_);

    if(t_loopInThisThread) {
        LOG_ERROR("Another EventLoop %p exists in this thread %d \n", t_loopInThisThread);
    }
    else {
        t_loopInThisThread = this;
    }

    wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead, this));
    wakeupChannel_->enableReading();
}

EventLoop::~EventLoop() {
    wakeupChannel_->disableAll();
    wakeupChannel_->remove();
    ::close(wakeupFd_);
    t_loopInThisThread = nullptr;
}

// 开启事件循环
void EventLoop::loop() {
    looping_ = true;
    quit_ = false;

    LOG_INFO(" [%s:%s:%d] EventLoop %p start looping \n", __FILE__, __FUNCTION__, __LINE__, this);

    while(!quit_) {
        activeChannels_.clear();
        pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);
        for(Channel *channel : activeChannels_) {
            channel->HandleEvent(pollReturnTime_); // 处理对应事件回调
        }
        doPendingFunctors();
    }
    
    LOG_INFO(" [%s:%s:%d] EventLoop %p stop looping \n", __FILE__, __FUNCTION__, __LINE__, this);
    looping_ = false;
}

// 退出事件循环
void EventLoop::quit() {
    quit_ = true;

    if(!isInLoopThread()) {
        wakeup();
    }
}

// 在当前loop中执行cb
void EventLoop::runInLoop(Functor cb) {
    if(isInLoopThread()) {
        cb();
    }
    else {
        queueInLoop(cb);
    }
}

// 把cb放入队列中，唤醒loop所在线程，执行cb
void EventLoop::queueInLoop(Functor cb) {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        pendingFunctors_.push_back(cb);
    }

    if(!isInLoopThread() || callingPendingFunctors_) {
        wakeup();
    }
}

// EventLoop方法 =》 Poller方法
void EventLoop::updateChannel(Channel* channel) {
    poller_->updateChannel(channel);
}
void EventLoop::removeChannel(Channel* channel) {
    poller_->removeChannel(channel);
}
bool EventLoop::hasChannel(Channel* channel) {
    return poller_->hasChannel(channel);
}

// 唤醒loop所在线程
void EventLoop::wakeup() {
    uint64_t one = 1;
    ssize_t n = write(wakeupFd_, &one, sizeof one);
    if(n != sizeof one) {
        LOG_ERROR("EventLoop::wakeup() writes %lu bytes instead of 8", n);
    }
}

// 接收唤醒
void EventLoop::handleRead() {
    uint64_t one = 1;
    ssize_t n = read(wakeupFd_, &one, sizeof one);
    if(n != sizeof one) {
        LOG_ERROR("EventLoop::handleRead() reads %lu bytes instead of 8", n);
    }
}

// 执行回调
void EventLoop::doPendingFunctors() {
    std::vector<Functor> functors;
    callingPendingFunctors_ = true;
    
    {
        std::unique_lock<std::mutex> lock(mutex_);
        functors.swap(pendingFunctors_);
    }

    for(const Functor& functor : functors) {
        functor();
    }
    
    callingPendingFunctors_ = false;
}