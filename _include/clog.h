#ifndef _CLOG_H_
#define _CLOG_H_

#include <bits/stdc++.h>
#include "define.h"
#include "timeTools.h"

using std::string;
using std::stringstream;

#define DEFAULT_LOG_PATH "log/"
#define MAX_LOG_MSG_SIZE 128

#define DEBUG_LOG(args...)      g_log->printLog(__FILE__, __FUNCTION__, __LINE__, STR_NO_BUG_LOG_DEBUG    , args)
#define INFO_LOG(args...)       g_log->printLog(__FILE__, __FUNCTION__, __LINE__, STR_NO_BUG_LOG_INFO     , args)
#define NOTICE_LOG(args...)     g_log->printLog(__FILE__, __FUNCTION__, __LINE__, STR_NO_BUG_LOG_NOTICE   , args)
#define WARN_LOG(args...)       g_log->printLog(__FILE__, __FUNCTION__, __LINE__, STR_NO_BUG_LOG_WARN     , args)
#define ERR_LOG(args...)        g_log->printLog(__FILE__, __FUNCTION__, __LINE__, STR_NO_BUG_LOG_ERR      , args)
#define CORE_ERR_LOG(args...)   g_log->printLog(__FILE__, __FUNCTION__, __LINE__, STR_NO_BUG_LOG_CORE_ERR , args)

typedef stringstream LogFormatterStr;

/**
    非线程安全的日志，第一版打算写成redis那种事件循环。就先不处理了
*/
class CLog {
public:
    void printLog(const char*file, const char* func, int line, const char* level, const char* fmt, ...);

    void writeLogFile(const char*file, const char* func, int line, const char* level, const char* buf);
private:
    char buf[MAX_LOG_MSG_SIZE];
};

/**
    C++11 可变参数发现不好用，然后用了c版的。。。(/ □ \)
*/
template<typename T>
void logFormatterToStr(LogFormatterStr &logs, T value) {
    logs << value;
}

template<typename T, typename... Args>
void logFormatterToStr(LogFormatterStr &logs, T value, Args... args) {
    logs << value << " ";
    logFormatterToStr(logs, args...);
}

#endif