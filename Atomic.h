#pragma once

#include "noncopyable.h"

#include <stdint.h>

template <typename T>
class AtomicIntegerT : noncopyable {
public:
    AtomicIntegerT() : value_(0) {

    }

    T get() { return __sync_val_compare_and_swap(&value_, 0, 0); }

    T getAndAdd(T x) {
        return __sync_fetch_and_add(&value_, x);
    }
    
    T addAndGet(T x) {
        return getAndAdd(x) + x;
    }

    T incrementAndGet() {
        return addAndGet(1);
    }
private:
    volatile T value_;
};

using AtomicInt32 = AtomicIntegerT<int32_t>;
using AtomicInt64 = AtomicIntegerT<int64_t>;