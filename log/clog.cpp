#include "clog.h"


void CLog::printLog(const char* level, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    char buf[512] = {};
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    std::cout << buf << std::endl;
}