#ifndef _CLOG_H_
#define _CLOG_H_

#include <bits/stdc++.h>
#include "define.h"

using std::string;
using std::stringstream;

#define DEFAULT_LOG_PATH "log/"

#define DEBUG_LOG(args...)   g_log.printLog(STR_NO_BUG_LOG_DEBUG, args)
#define INFO_LOG(args...)    g_log.printLog(NO_BUG_LOG_INFO     , args)
#define NOTICE_LOG(args...)  g_log.printLog(NO_BUG_LOG_NOTICE   , args)
#define WARN_LOG(args...)    g_log.printLog(NO_BUG_LOG_WARN     , args)
#define ERR_LOG(args...)     g_log.printLog(NO_BUG_LOG_ERR      , args)

typedef stringstream LogFormatterStr;

class CLog {
public:
    void printLog(const char* level, const char* fmt, ...);
private:

};

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