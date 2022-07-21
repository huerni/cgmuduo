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
    // 按时间格式打印时间
    std::string toString() const;
private:
    int64_t microSecondsSinceEpoch_;
};