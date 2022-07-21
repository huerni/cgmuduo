#include "Poller.h"
#include "EpollPoller.h"

#include <stdlib.h>

/**
 * 最好不要将获取派生类实例实现写在基类实现文件汇总，防止基类引用派生类文件，这样不好
 * 可以在第三方文件中引入基类和派生类，实现派生类实例
*/
Poller* Poller::newDefaultPoller(EventLoop* loop) {
    if(::getenv("MUDUO_USE_POLL")) {
        return nullptr; // 生成poll实例
    }
    return new EpollPoller(loop); // 生成epoll实例
}