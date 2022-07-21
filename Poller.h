#pragma once

#include "noncopyable.h"
#include "Timestamp.h"
#include <vector>
#include <unordered_map>

class EventLoop;
class Channel;

/**
 * IO复用封装类，封装POLL，EPOLL功能函数，统一对外接口
*/
class Poller : noncopyable {
public:
    using ChannelList = std::vector<Channel*>;

    Poller(EventLoop* loop);
    virtual ~Poller() = default;

    // poller统一接口，包括操作，更新，删除，由继承实现
    virtual Timestamp poll (int timeoutMs, ChannelList *activeChannels) = 0;
    virtual void updateChannel(Channel* channel) = 0;
    virtual void removeChannel(Channel* channel) = 0;

    // 判断通道是否在该IO复用中
    bool hasChannel(Channel* channel) const;

    // 获取loop默认IO复用具体实现
    static Poller* newDefaultPoller(EventLoop* loop);
protected:
    using ChannelMap = std::unordered_map<int, Channel*>;
    ChannelMap channels_;
private:
    EventLoop* ownerloop_;

};