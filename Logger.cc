#include "Logger.h"
#include "Timestamp.h"
#include <iostream>
#include <unistd.h>

// 单例模式，获取唯一单例对象
// 懒汉模式
Logger& Logger::instance(){
    static Logger logger;
    return logger;
}

// 设置日志级别
void Logger::setLogLevel(int level) {
    logLevel_ = level;
}

// 写日志 [级别信息] time : msg
void Logger::log(std::string msg) {

    std::cout<< Timestamp::now().toString() <<" ";
    std::cout<< getpid() << " ";

    switch (logLevel_)
    {
    case INFO:
        std::cout << "[INFO] ";
        break;
    case ERROR:
        std::cout << "[ERROR] ";
        break;
    case FATAL:
        std::cout << "[FATAL] ";
        break;
    case DEBUG:
        std::cout << "[DEBUG] ";
        break;
    }
    
    std::cout << msg <<std::endl;
}