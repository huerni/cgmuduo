#include "EventLoopThreadPool.h"
#include "EventLoopThread.h"
#include "Logger.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop, const std::string &name) 
        : baseLoop_(baseLoop), name_(name), started_(false), numThreads_(0), next_(0) {

}

EventLoopThreadPool::~EventLoopThreadPool() {

}

// 开启线程池，创建指定数量的loop thread
void EventLoopThreadPool::start(const ThreadInitCallBack &cb) {

    LOG_INFO("[%s:%s:%d] Thread number is %d \n", __FILE__, __FUNCTION__, __LINE__, numThreads_);

    started_ = true;
    
    for(int i = 0; i<numThreads_; ++i) {

        char buf[name_.size() + 32];
        
        snprintf(buf, sizeof buf, "%s%d", name_.c_str(), i);
        EventLoopThread *t = new EventLoopThread(cb, buf);
        threads_.push_back(std::unique_ptr<EventLoopThread>(t));
        loops_.push_back(t->startLoop());
    }
    
    if(numThreads_ == 0 && cb) {
        cb(baseLoop_);
    }
}

EventLoop* EventLoopThreadPool::getNextLoop() {
    EventLoop *loop = baseLoop_;

    if(!loops_.empty()) {
        loop = loops_[next_];
        ++next_;
        if(next_ >= loops_.size()) {
            next_ = 0;
        }
    }

    return loop;
}
    
std::vector<EventLoop*> EventLoopThreadPool::getAllLoops() {
    if(loops_.empty()) {
        return std::vector<EventLoop*>(1, baseLoop_);
    }
    else {
        return loops_;
    }
}