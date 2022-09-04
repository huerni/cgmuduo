#pragma once

#include "noncopyable.h"

#include <string>
#include <functional>
#include <vector>
#include <memory>

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool : noncopyable {
public:
    using ThreadInitCallBack = std::function<void(EventLoop*)>;

    EventLoopThreadPool(EventLoop *baseLoop, const std::string &name);
    ~EventLoopThreadPool();

    void setThreadNum(int numThreads) { numThreads_ = numThreads; }
    
    void start(const ThreadInitCallBack &cb = ThreadInitCallBack());

    EventLoop* getNextLoop();
    
    std::vector<EventLoop*> getAllLoops();

    bool started() const { return started_; }
    const std::string name() const { return name_; }
private:
    // 主loop，最开始用户创建的loop，在多线程环境下，可看做reactor，用来分发线程
    EventLoop *baseLoop_;
    std::string name_;
    bool started_;
    int numThreads_;  //　线程数量
    int next_;
    // 线程池中的线程与loop
    std::vector<std::unique_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> loops_;
};