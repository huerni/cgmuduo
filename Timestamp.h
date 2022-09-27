#pragma once

#include <iostream>

/**
 * 时间类，打印当前时间
*/
class Timestamp{
public:
    Timestamp();
    explicit Timestamp(int64_t microSecondsSinceEpoch);
    // 获取当前时间
    static Timestamp now();
    
    static Timestamp invalid() {
        return Timestamp();
    }
    // 按时间格式打印时间
    std::string toString() const;
    int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }

    static const int kMicroSecondsPerSecond = 1000 * 1000;

private:
    int64_t microSecondsSinceEpoch_;
};

inline double timeDifference(Timestamp high, Timestamp low) {
    int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();

    return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
}

inline Timestamp addTime(Timestamp timestamp, double seconds) {
    int64_t delta = static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond);

    return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
}