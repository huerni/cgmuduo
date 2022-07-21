#include "EpollPoller.h"
#include "Logger.h"
#include "Channel.h"
#include <memory.h>
#include <unistd.h>

const int KNew = -1;
const int KAdded = 1;
const int KDeleted = 2;

EpollPoller::EpollPoller(EventLoop* loop) 
    : Poller(loop), epollfd_(::epoll_create1(EPOLL_CLOEXEC)), events_(kInitEventListSize) { 
        if(epollfd_ < 0) {
            LOG_FATAL("epoll_create error:%d", errno);
        }
}

EpollPoller::~EpollPoller(){
    ::close(epollfd_);
}

// epoll_wait监听events中的事件，并将活跃通道返回给所属的loop
Timestamp EpollPoller::poll (int timeoutMs, ChannelList *activeChannels) {
    LOG_INFO("func=%s => fd total count=%d \n", __FUNCTION__, channels_.size());
    
    int numEvents = ::epoll_wait(epollfd_, &*events_.begin(), static_cast<int>(events_.size()), timeoutMs);
    int saveErrno = errno;
    Timestamp now(Timestamp::now());

    if(numEvents > 0) {
        LOG_INFO("%d events happened \n", numEvents);
        fillActiveChannels(numEvents, activeChannels);
        if(numEvents == events_.size()) {
            events_.resize(numEvents * 2);
        }
    }
    else if(numEvents == 0) {
        LOG_INFO("%s timeout! \n", __FUNCTION__);
    }
    else {
        if(saveErrno != EINTR) {
            errno = saveErrno;
            LOG_ERROR("EpollPoller::poll() err!");
        }
    }
    return now;
}

// 更新channel  如果没在Poller中，则添加，否则有活动，修改，如果没有活动，从Poller监测中移除(EPOLL_CTL_DEL)，但不移除map
void EpollPoller::updateChannel(Channel* channel) {
    const int index = channel->index();
    LOG_INFO("func=%s => fd=%d, events=%d, index=%d \n", __FUNCTION__, channel->fd(), channel->events(), channel->index());
    if(index == KNew || index == KDeleted) {
        if(index == KNew) {
            int fd = channel->fd();
            channels_[fd] = channel;
        }
        channel->set_index(KAdded);
        update(EPOLL_CTL_ADD, channel);
    }
    else {
        int fd = channel->fd();
        if(channel->isNoneEvent()) {
            update(EPOLL_CTL_DEL, channel);
            channel->set_index(KDeleted);
        }
        else {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

// 从Poller中删除channel，即移除map，如果已被Poller监测，则从Poller中移除(EPOLL_CTL_DEL)
void EpollPoller::removeChannel(Channel* channel) {
    int fd = channel->fd();
    int index = channel->index();
    LOG_INFO("func=%s => fd=%d, index=%d \n", __FUNCTION__, channel->fd(), channel->index());
    if(index == KAdded) {
        update(EPOLL_CTL_DEL, channel);
    }
    channels_.erase(fd);
    channel->set_index(KNew);
}

// 填充活跃通道
void EpollPoller::fillActiveChannels(int numEvents, ChannelList* activeChannels) {
    LOG_INFO("func=%s => num total count=%d", numEvents);
    
    for(int i = 0; i<numEvents; ++i) {
        Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->set_revents(events_[i].events);
        activeChannels->push_back(channel);
    }
}

// 指定操作更新通道 epoll_ctl具体操作  add/mod/del
void EpollPoller::update(int operation, Channel *channel) {
    int fd = channel->fd();
    epoll_event event;
    bzero(&event, sizeof event);
    event.events = channel->events();
    event.data.ptr = channel;
    event.data.fd = fd;

    if(::epoll_ctl(epollfd_, operation, fd, &event) < 0) {
        if(operation == EPOLL_CTL_DEL) {
            LOG_ERROR("epoll_ctl del error: %d \n", errno);
        }
        else {
            LOG_FATAL("epoll_ctl add/mod error: %d \n", errno);
        }
    }
}