#pragma once

#include <string>

#include "noncopyable.h"


// 写四种级别宏，方便使用

// ... 可变参数 LOG_INFO("%s, %d", arg1, args)
// __VA_ARGS__ 获取可变参数宏
#define LOG_INFO(logmsgFormat, ...) \
    do { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(INFO); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while (0);

#define LOG_ERROR(logmsgFormat, ...) \
    do { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(ERROR); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while (0);

#define LOG_FATAL(logmsgFormat, ...) \
    do { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(FATAL); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
        exit(-1); \
    } while (0);


#ifdef MUDEBUG
// 只定义MUDEBUG宏时，DEBUG日志才输出，否则不做任何动作
    #define LOG_DEBUG(logmsgFormat, ...) \
        do { \
            Logger &logger = Logger::instance(); \
            logger.setLogLevel(DEBUG); \
            char buf[1024] = {0}; \
            snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__) \
            logger.log(buf); \
        } while (0);
#else
    #define LOG_DEBUG(logmsgFormat, ...)
#endif


// 定义日志级别
enum LogLevel { 
    INFO,  // 普通信息
    ERROR,  // 错误信息
    FATAL,  // core信息
    DEBUG   // 调试信息
};

/**
 * 日志类，有INFO,ERROR,FATAL,DEBUG四种日志级别，包括设置日志级别，写日志功能
*/
class Logger : noncopyable {
public:
    // 单例模式，获取唯一单例对象
    static Logger& instance();
    // 设置日志级别
    void setLogLevel(int level);
    // 写日志
    void log(std::string msg);

private:
    int logLevel_;
};