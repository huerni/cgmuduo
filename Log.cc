
#include "Log.h"

#include <iostream>
#include <functional>
#include "Timestamp.h"


const char* LogLevel::ToString(LogLevel::Level level) {
    switch(level) {
        case LogLevel::DEBUG: return "DEBUG"; break;
        case LogLevel::INFO: return "INFO"; break;
        case LogLevel::ERROR: return "ERROR"; break;
        case LogLevel::FATAL: return "FATAL"; break;
        default:
            return "UNKNOW";
    }
    return "UNKNOW";
}

LogLevel::Level LogLevel::FromString(const std::string& str) {
    if(str == "debug" || str == "DEBUG")
        return LogLevel::DEBUG;
    if(str == "info" || str == "INFO")
        return LogLevel::INFO;
    if(str == "ERROR" || str == "error")
        return LogLevel::ERROR;
    if(str == "FATAL" || str == "fatal")
        return LogLevel::FATAL;

    return LogLevel::UNKNOW;
}


LogEventWrap::LogEventWrap(LogEvent::ptr e) : event_(e) {

}

LogEventWrap::~LogEventWrap() {
    event_->getLogger()->log(event_->getLevel(), event_);
}

void LogEvent::format(const char* fmt, ...) {
    va_list al;
    va_start(al, fmt);
    format(fmt, al);
    va_end(al);
}


void LogEvent::format(const char* fmt, va_list al) {
    char* buf = nullptr;
    int len = vasprintf(&buf, fmt, al);
    if(len != -1) {
        ss_ << std::string(buf, len);
        free(buf);
    }
}

std::stringstream& LogEventWrap::getSS() {
    return event_->getSS();
}

void LogAppender::setFormatter(LogFormatter::ptr val) {
    //MutexType::Lock lock(mutex_);
    formatter_ = val;
    if(formatter_) {
        hasFormatter_ = true;
    }
    else {
        hasFormatter_ = false;
    }
}

LogFormatter::ptr LogAppender::getFormatter(){
    //MutexType::Lock lock(mutex_);
    return formatter_;
}

class MessageFormatItem : public LogFormatter::FormatItem {
public:
    MessageFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getContent();
    }
};

class LevelFormatItem : public LogFormatter::FormatItem {
public:
    LevelFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << LogLevel::ToString(level);
    }
};

class ElapseFormatItem : public LogFormatter::FormatItem {
public:
    ElapseFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getElapse();
    }
};

class NameFormatItem : public LogFormatter::FormatItem {
public:
    NameFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getLogger()->getName();
    }
};

class ThreadIdFormatItem : public LogFormatter::FormatItem {
public:
    ThreadIdFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getThreadId();
    }
};

class ThreadNameFormatItem : public LogFormatter::FormatItem {
public:
    ThreadNameFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getThreadName();
    }
};

class DateTimeFormatItem : public LogFormatter::FormatItem {
public:
    DateTimeFormatItem(const std::string& format = "%Y-%m-%d %H:%M:%S")
        :m_format(format) {
        if(m_format.empty()) {
            m_format = "%Y-%m-%d %H:%M:%S";
        }
    }

    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        struct tm tm;
        time_t time = event->getTime();
        localtime_r(&time, &tm);
        char buf[64];
        strftime(buf, sizeof(buf), m_format.c_str(), &tm);
        os << buf;
    }
private:
    std::string m_format;
};

class FilenameFormatItem : public LogFormatter::FormatItem {
public:
    FilenameFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getFile();
    }
};

class LineFormatItem : public LogFormatter::FormatItem {
public:
    LineFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getLine();
    }
};

class NewLineFormatItem : public LogFormatter::FormatItem {
public:
    NewLineFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << std::endl;
    }
};

class StringFormatItem : public LogFormatter::FormatItem {
public:
    StringFormatItem(const std::string& str)
        :str_(str) {}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << str_;
    }
private:
    std::string str_;
};

class TabFormatItem : public LogFormatter::FormatItem {
public:
    TabFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << "\t";
    }
};

LogEvent::LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level
            ,const char* file, int32_t line, uint32_t elapse
            , uint32_t thread_id, uint64_t time
            , const std::string& thread_name) 
        : file_(file)
        , line_(line)
        , elapse_(elapse)
        , threadId_(thread_id)
        , time_(time)
        , threadName_(thread_name)
        , logger_(logger)
        , level_(level) {

}

Logger::Logger(const std::string& name)
        :name_(name)
        , level_(LogLevel::DEBUG) {
    formatter_.reset(new LogFormatter(("%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]:%l%T%m%n")));
}

void Logger::setFormatter(LogFormatter::ptr val) {
    //MutexType::Lock lock(mutex_);
    formatter_ = val;
    
    for(auto& appender : appenders_) {
        //MutexType::Lock ll(appender->mutex_);
        if(!appender->hasFormatter_) {
            appender->formatter_ = formatter_;
        }
    }
}

void Logger::setFormatter(const std::string& val) {
    std::cout<< "---" << val <<std::endl;
    LogFormatter::ptr new_val(new LogFormatter(val));
    if(new_val->isError()) {
        std::cout << "Logger setFormatter name=" << name_
                << " value=" << val <<" invalid formatter" <<std::endl;
        return ;
    }
    setFormatter(new_val);
}


LogFormatter::ptr Logger::getFormatter() {
    //MutexType::Lock lock(mutex_);
    return formatter_;
}

void Logger::addAppender(LogAppender::ptr appender) {
    //MutexType::Lock lock(mutex_);
    if(!appender->getFormatter()) {
        //MutexType::Lock ll(appender->mutex_);
        appender->formatter_ = formatter_;
    }
    appenders_.push_back(appender);
}

void Logger::delAppender(LogAppender::ptr appender) {
     //MutexType::Lock lock(mutex_);
     for(auto it = appenders_.begin(); it != appenders_.end(); ++it) {
        if(*it == appender) {
            appenders_.erase(it);
            break;
        }
     }
}

void Logger::clearAppenders() {
    //MutexType::Lock lock(mutex_);
    appenders_.clear();
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event) {
    if(level >= level_) {
        auto self = shared_from_this();
        //MutexType::Lock lock(mutex_);
        if(!appenders_.empty()) {
            for(auto& i : appenders_) {
                i->log(self, level, event);
            }
        }
        else if(root_) {
            root_->log(level, event);
        }
    }
}

void Logger::debug(LogEvent::ptr event) {
    log(LogLevel::DEBUG, event);
}

void Logger::info(LogEvent::ptr event) {
    log(LogLevel::INFO, event);
}

void Logger::error(LogEvent::ptr event) {
    log(LogLevel::ERROR, event);
}

void Logger::fatal(LogEvent::ptr event) {
    log(LogLevel::FATAL, event);
}


FileLogAppender::FileLogAppender(const std::string& filename)
    :filename_(filename) {
    reopen();
}

void FileLogAppender::log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) {
    if(level >= level_) {
        uint64_t now = event->getTime();
        if(now >= (lastTime_+3)) {
            reopen();
            lastTime_ = now;
        }
        //MutexType::Lock lock(mutex_);
        if(!formatter_->format(filestream_, logger, level, event)) {
            std::cout<< "error"<<std::endl;
        }
    }
}


bool FileLogAppender::reopen() {
    //MutexType::Lock lock(mutex_);
    if(filestream_) {
        filestream_.close();
    }
    //return OpenForWrite(filestream_, filename, std::ios::app);
    return true;
}

void StdoutLogAppender::log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) {
    if(level >= level_) {
        //MutexType::Lock lock(mutex_);
        formatter_->format(std::cout, logger, level, event);
    }
}


LogFormatter::LogFormatter(const std::string& pattern)
    : pattern_(pattern) {
    init();
}

std::string LogFormatter::format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) {
    std::stringstream ss;
    for(auto& i : items_) {
        i->format(ss, logger, level, event);
    }
    return ss.str();
}

std::ostream& LogFormatter::format(std::ostream& ofs, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) {
    for(auto& i : items_) {
        i->format(ofs, logger, level, event);
    }
    return ofs;
}

// 初始化日志格式
//%x%x{%x%x}
void LogFormatter::init() {
    // str, format, type
    std::vector<std::tuple<std::string, std::string, int> > vec;
    std::string nstr;
    for(size_t i = 0; i<pattern_.size(); ++i) {
        if(pattern_[i] != '%') {
            nstr.append(1, pattern_[i]);
            continue;
        }
        // 转义
        if((i+1) < pattern_.size()) {
            if(pattern_[i+1] == '%') {
                nstr.append(1, '%');
                continue;
            }
        }

        size_t n = i+1;
        int fmt_status = 0;
        size_t fmt_begin = 0;

        std::string str;
        std::string fmt;
        while(n < pattern_.size()) {
            if(!fmt_status && (!isalpha(pattern_[n]) && pattern_[n] != '{' && pattern_[n] != '}')) {
                str = pattern_.substr(i+1, n-i-1);
                break;
            }

            if(fmt_status == 0) {
                if(pattern_[n] == '{') {
                    str = pattern_.substr(i+1, n-i-1);
                    fmt_status = 1;
                    fmt_begin = n;
                    ++n;
                    continue;
                }
            }
            else if(fmt_status == 1) {
                if(pattern_[n] == '}') {
                    fmt = pattern_.substr(fmt_begin+1, n-fmt_begin-1);
                    fmt_status = 0;
                    ++n;
                    break;
                }
            }

            ++n;
            if(n == pattern_.size()) {
                if(str.empty()) {
                    str = pattern_.substr(i+1);
                }
            }
        } // end while

        if(fmt_status == 0) {
            if(!nstr.empty()) {
                vec.push_back(std::make_tuple(nstr, std::string(), 0));
                nstr.clear();
            }
            vec.push_back(std::make_tuple(str, fmt, 1));
            i = n-1;
        }
        else if(fmt_status == 1) {
            error_ = true;
            vec.push_back(std::make_tuple("<<pattern_error>>", fmt, 0));
        }
    } // end for
    
    if(!nstr.empty()) {
        vec.push_back(std::make_tuple(nstr, "", 0));
    }

    static std::map<std::string, std::function<FormatItem::ptr(const std::string& str)> > s_format_items = {
#define XX(str, C) \
        {#str, [](const std::string& fmt) { return FormatItem::ptr(new C(fmt));}}

        XX(m, MessageFormatItem),           //m:消息
        XX(p, LevelFormatItem),             //p:日志级别
        XX(r, ElapseFormatItem),            //r:累计毫秒数
        XX(c, NameFormatItem),              //c:日志名称
        XX(t, ThreadIdFormatItem),          //t:线程id
        XX(n, NewLineFormatItem),           //n:换行
        XX(d, DateTimeFormatItem),          //d:时间
        XX(f, FilenameFormatItem),          //f:文件名
        XX(l, LineFormatItem),              //l:行号
        XX(T, TabFormatItem),               //T:Tab
        XX(N, ThreadNameFormatItem),        //N:线程名称
#undef XX
    };  

    for(auto& i : vec) {
        if(std::get<2>(i) == 0) {
            items_.push_back(FormatItem::ptr(new StringFormatItem(std::get<0>(i))));
        }
        else {
            auto it = s_format_items.find(std::get<0>(i));
            if(it == s_format_items.end()) {
                items_.push_back(FormatItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>")));
                error_ = true;
            }
            else {
                items_.push_back(it->second(std::get<1>(i)));
            }
        }
    }
}

LoggerManager::LoggerManager() {
    root_.reset(new Logger);
    root_->addAppender(LogAppender::ptr(new StdoutLogAppender));

    loggers_[root_->name_] = root_;

    init();
}

Logger::ptr LoggerManager::getLogger(const std::string& name) {
    auto it = loggers_.find(name);
    if(it != loggers_.end()) {
        return it->second;
    }

    Logger::ptr logger(new Logger(name));
    logger->root_ = root_;
    loggers_[name] = logger;
    return logger;
}

LoggerManager* LoggerManager::instance() {
    static LoggerManager loggerManager;

    return &loggerManager;
}


