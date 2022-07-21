#pragma once

#include "Poller.h"
#include "Timestamp.h"
#include <vector>
#include <sys/epoll.h>

class Channel;
class EventLoop;

/**
 *  epoll使用
 *  epoll_creat()
 *  epoll_ctl()  add/mod/del
 *  epoll_wait() 
*/
class EpollPoller : public Poller {
public:
    EpollPoller(EventLoop* loop);
    ~EpollPoller() override;

    // 重写基类接口
    Timestamp poll (int timeoutMs, ChannelList *activeChannels) override;
    void updateChannel(Channel* channel) override;
    void removeChannel(Channel* channel) override;

private:
    static const int kInitEventListSize = 16;

    // 填充活跃通道
    void fillActiveChannels(int numEvents, ChannelList* activeChannels);
    // 指定更新通道
    void update(int operation, Channel *channel);

    using EventList = std::vector<epoll_event>;

    int epollfd_;
    EventList events_;
};