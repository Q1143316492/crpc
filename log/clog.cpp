#include "clog.h"


void CLog::printLog(const char* level, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(this->buf, sizeof(this->buf), fmt, ap);
    va_end(ap);
    this->writeLogFile(level, this->buf);
}

void CLog::writeLogFile(const char* level, const char* buf)
{
    std::ofstream fs;
    std::stringstream ss;
    ss << DEFAULT_LOG_PATH;
    ss << serializeDate('-') << ".log";
    fs.open(ss.str(), std::ios::app);
    if (!fs.is_open()) {
        return ;
    }
    fs << "[" << serializeDateTime() << "]";
    fs << "[" << level << "]";
    fs << "[" << buf << "]" << std::endl;
    fs.close();
}