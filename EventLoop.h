#pragma once


#include <functional>
#include <vector>
#include <atomic>
#include <memory>
#include <mutex>

#include "Timestamp.h"
#include "Poller.h"
#include "CurrentThread.h"


class Channel;

/**
 * 事件循环类，包含Poller与Channel两大模块
*/
class EventLoop : noncopyable{
public:
    using Functor = std::function<void()>;

    EventLoop();
    ~EventLoop();

    // 开启事件循环
    void loop();

    // 退出事件循环
    void quit();

    Timestamp pollReturnTime() const { return pollReturnTime_; }

    // 在当前loop中执行cb
    void runInLoop(Functor cb);
    // 把cb放入队列中，唤醒loop所在线程，执行cb
    void queueInLoop(Functor cb);

    // 唤醒loop所在线程
    void wakeup();

    // EventLoop方法 =》 Poller方法
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);
    bool hasChannel(Channel* channel);

    // 判断EventLoop对象是否在自己线程里面
    bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }

private:
    void handleRead(); // wake up
    void doPendingFunctors(); // 执行回调

    using ChannelList = std::vector<Channel*>;

    std::atomic_bool looping_; // 原子操作  判断loop是否在事件循环
    std::atomic_bool quit_;  // 标识退出loop循环

    const pid_t threadId_;  // loop所在线程id
    Timestamp pollReturnTime_;  // poller返回发生事件的channels的时间点
    std::unique_ptr<Poller> poller_;  // loop所使用的poller

    int wakeupFd_;  // eventfd 用于线程间通信，通过轮询算法唤醒subloop
    std::unique_ptr<Channel> wakeupChannel_; // 将eventfd封装成channel

    ChannelList activeChannels_;  // poller监听返回的活跃channel集合

    std::atomic_bool callingPendingFunctors_;  // 判断loop是否有新的回调需要执行
    std::vector<Functor> pendingFunctors_; // 待处理的回调集合
    std::mutex mutex_; // 互斥锁
};