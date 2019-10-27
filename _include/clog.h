#ifndef _CLOG_H_
#define _CLOG_H_

#include <bits/stdc++.h>

using namespace std;

string LOG_LEVEL[]  = 
{
    "stderr",    //0：控制台错误
    "emerg",     //1：紧急
    "alert",     //2：警戒
    "crit",      //3：严重
    "error",     //4：错误
    "warn",      //5：警告
    "notice",    //6：注意
    "info",      //7：信息
    "debug"      //8：调试
};

class CLog {
public:

    void DEBUG_LOG();
    void INFO_LOG();
    void NOTICE_LOG();
    void WARN_LOG();
    void ERR_LOG();

    void PRINT_LOG(string level);

private:


};

#endif