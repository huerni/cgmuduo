#include "Thread.h"
#include "CurrentThread.h"

#include <semaphore.h>

// 静态类成员变量需在类外单独初始化
std::atomic_int Thread::numCreated_(0);


Thread::Thread(ThreadFunc func, const std::string &name)
        : started_(false), joined_(false), tid_(0), func_(std::move(func)), name_(name) {
    setDefaultName();
}

// 线程若运行，需执行相关动作  若没有运行，析构函数啥也不干
Thread::~Thread() {
    if(started_ && !joined_) {
        thread_->detach();  // 分离线程
    }
}


void Thread::start() {
    started_  = true;
    sem_t sem;
    sem_init(&sem, false, 0);

    // 开启线程
    thread_ = std::shared_ptr<std::thread>(new std::thread([&](){
        tid_ = CurrentThread::tid();
        sem_post(&sem);
        func_();
    }));
    
    // 这里需要等待获取上面新创建的线程的tid值
    // 所以使用信号量先进行阻塞，直到获得tid值
    sem_wait(&sem);
}

void Thread::join() {
    joined_ = true;
    thread_->join();
}

// 线程名
void Thread::setDefaultName() {
    int num = ++numCreated_;
    if(name_.empty()) {
        char buf[32] = {0};
        snprintf(buf, sizeof buf, "Thread%d", num);
        name_ = buf;
    }
}