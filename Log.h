
#pragma once

#include <memory>
#include <string>
#include <mutex>
#include <sstream>
#include <vector>
#include <list>
#include <fstream>
#include <map>
#include <stdarg.h>
#include "CurrentThread.h"

#define LOG_LEVEL(logger, level) \
    if(logger->getLevel() <= level) \
        LogEventWrap(LogEvent::ptr(new LogEvent(logger, level, \
                    __FILE__, __LINE__, 0, CurrentThread::tid(), time(0), "thread"))).getSS();

#define LOG_DEBUG(logger) LOG_LEVEL(logger, LogLevel::DEBUG)

#define LOG_INFO(logger) LOG_LEVEL(logger, LogLevel::INFO);

#define LOG_ERROR(logger) LOG_ERROR(logger, LogLevel::ERROR);

#define LOG_FATAL(logger) LOG_LEVEL(logger, LogLevel::FATAL);

#define LOG_FMT_LEVEL(logger, level, fmt, ...) \
    if(logger->getLevel() <= level) \
        LogEventWrap(LogEvent::ptr(new LogEvent(logger, level, \
                    __FILE__, __LINE__, 0, CurrentThread::tid(), time(0), "thread"))).getEvent()->format(fmt, __VA_ARGS__)

#define LOG_FMT_DEBUG(logger, fmt, ...) LOG_FMT_LEVEL(logger, LogLevel::DEBUG, fmt, __VA_ARGS__)

#define LOG_FMT_INFO(logger, fmt, ...) LOG_FMT_LEVEL(logger, LogLevel::INFO, fmt, __VA_ARGS__)

#define LOG_FMT_ERROR(logger, fmt, ...) LOG_FMT_LEVEL(logger, LogLevel::ERROR, fmt, __VA_ARGS__)

#define LOG_FMT_FATAL(logger, fmt, ...) LOG_FMT_LEVEL(logger, LogLevel::FATAL, fmt, __VA_ARGS__)


#define LOG_ROOT() LoggerManager::instance()->getRoot()

#define LOG_NAME(name) LoggerManager::instance()->getLogger(name)



class Logger;
class LoggerManager;

class LogLevel {
public:
    enum Level{
        UNKNOW = 0,
        DEBUG = 1,
        INFO = 2,
        ERROR = 3,
        FATAL = 4
    };

    static const char* ToString(LogLevel::Level level);

    static LogLevel::Level FromString(const std::string& str);

};

class LogEvent{
public:
    typedef std::shared_ptr<LogEvent> ptr;

    LogEvent(std::shared_ptr<Logger> logger
            , LogLevel::Level level
            , const char* file, int32_t line, uint32_t elapse
            , uint32_t thread_id
            , uint64_t time
            , const std::string& thread_name);

    const char* getFile() const { return file_; }
    int32_t getLine() const { return line_; }
    uint32_t getElapse() const { return elapse_; }
    uint32_t getThreadId() const { return threadId_; }
    uint64_t getTime() const { return time_; }
    const std::string& getThreadName() const { return threadName_; }
    std::string getContent() const { return ss_.str(); }
    std::shared_ptr<Logger> getLogger() const { return logger_; }
    LogLevel::Level getLevel() const { return level_; }
    std::stringstream& getSS() { return ss_; }

    void format(const char* fmt, ...);

    void format(const char* fmt, va_list al);
private: 
    const char* file_ = nullptr;
    int32_t line_ = 0;
    uint32_t elapse_ = 0;
    uint32_t threadId_ = 0;
    uint64_t time_ = 0;

    std::string threadName_;
    std::stringstream ss_;
    std::shared_ptr<Logger> logger_;
    LogLevel::Level level_;
};

class LogEventWrap {
public:
    LogEventWrap(LogEvent::ptr e);

    ~LogEventWrap();

    LogEvent::ptr getEvent() const { return event_; }

    std::stringstream& getSS();
private:
    LogEvent::ptr event_;
};

class LogFormatter {
public:
    typedef std::shared_ptr<LogFormatter> ptr;

    LogFormatter(const std::string& pattern);

    std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
    std::ostream& format(std::ostream& ofs, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);

public:
    class FormatItem {
    public:
        typedef std::shared_ptr<FormatItem> ptr;

        virtual ~FormatItem() {}
        virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);

    };
    void init();
    bool isError() const { return error_; }

    const std::string getPattern() const { return pattern_; }
private:
    std::string pattern_;
    std::vector<FormatItem::ptr> items_;
    bool error_ = false;

};

class LogAppender {
friend class Logger;
public:
    typedef std::shared_ptr<LogAppender> ptr;
    typedef pthread_spinlock_t MutexType;

    virtual ~LogAppender() {}

    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
    void setFormatter(LogFormatter::ptr val);

    LogFormatter::ptr getFormatter();

    LogLevel::Level getLevel() const { return level_; }
    void setLevel(LogLevel::Level val) { level_ = val; }
protected:
    LogLevel::Level level_ = LogLevel::DEBUG;
    bool hasFormatter_ = false;
    MutexType mutex_;
    LogFormatter::ptr formatter_;
};

class Logger : public std::enable_shared_from_this<Logger> {
friend class LoggerManager;
public:
    typedef std::shared_ptr<Logger> ptr;
    typedef pthread_spinlock_t MutexType;

    Logger(const std::string& name = "root");

    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);

    void info(LogEvent::ptr event);

    void error(LogEvent::ptr event);

    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);

    void delAppender(LogAppender::ptr appender);

    void clearAppenders();

    LogLevel::Level getLevel() const { return level_; }

    void setLevel(LogLevel::Level val) { level_ = val; }

    const std::string& getName() const { return name_; }

    void setFormatter(LogFormatter::ptr val);

    void setFormatter(const std::string& val);

    LogFormatter::ptr getFormatter();

private:
    std::string name_;
    LogLevel::Level level_;
    MutexType mutex_;
    std::list<LogAppender::ptr> appenders_;
    LogFormatter::ptr formatter_;
    Logger::ptr root_;
};

class StdoutLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;
};

class FileLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string& filename);
    void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;

    bool reopen();
private:
    std::string filename_;
    std::ofstream filestream_;
    uint64_t lastTime_ = 0;
};

class LoggerManager {
public:
    typedef pthread_spinlock_t MutexType;

    static LoggerManager* instance();

    Logger::ptr getLogger(const std::string& name);

    void init();

    Logger::ptr getRoot() const { return root_; }

private:
    LoggerManager();
    MutexType mutex_;
    std::map<std::string, Logger::ptr> loggers_;
    Logger::ptr root_;
};