#pragma once

/**
 * 获取当前线程的pid，需要用到线程参数
*/
namespace CurrentThread {
    extern __thread int t_cachedTid;

    void cacheTid();

    inline int tid() {
        if(__builtin_expect(t_cachedTid == 0, 0)) {
            cacheTid();
        }
        return t_cachedTid;
    }
};
