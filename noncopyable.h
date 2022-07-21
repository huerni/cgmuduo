#pragma once

/**
 * 派生类对象正常构造析构，禁止拷贝构造与赋值函数
 */
class noncopyable{
public:
    noncopyable(const noncopyable& ) = delete;
    void operator = (const noncopyable& ) = delete;
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};