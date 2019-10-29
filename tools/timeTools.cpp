#include "timeTools.h"

/**
struct tm {
  int tm_sec;   // 秒，正常范围从 0 到 59，但允许至 61
  int tm_min;   // 分，范围从 0 到 59
  int tm_hour;  // 小时，范围从 0 到 23
  int tm_mday;  // 一月中的第几天，范围从 1 到 31
  int tm_mon;   // 月，范围从 0 到 11
  int tm_year;  // 自 1900 年起的年数
  int tm_wday;  // 一周中的第几天，范围从 0 到 6，从星期日算起
  int tm_yday;  // 一年中的第几天，范围从 0 到 365，从 1 月 1 日算起
  int tm_isdst; // 夏令时
}
*/

tm getDateTime()
{
    time_t now = time(0);
    return *localtime(&now);
}

string serializeDate(char split)
{
    tm ltm = getDateTime();
    stringstream ss;
    ss << (ltm.tm_year + 1900) << split << (ltm.tm_mon + 1) << split << ltm.tm_mday;
    return ss.str();
}

string serializeDateTime()
{
    tm ltm = getDateTime();
    stringstream ss;
    ss << (ltm.tm_year + 1900) << "/" << (ltm.tm_mon + 1) << "/" << ltm.tm_mday << "-";
    ss << setw(2) << setfill('0') << ltm.tm_hour << ":";
    ss << setw(2) << setfill('0') << ltm.tm_min << ":";
    ss << setw(2) << setfill('0') << ltm.tm_sec;
    return ss.str();
}