#ifndef _SERVER_H_
#define _SERVER_H_

#include "unistd.h"
#include "define.h"
#include "clog.h"

extern CLog *g_log;

struct ProcessMsg {
    pid_t pid;
    pid_t ppid;
    u_int procType;
};

class CServer {
public:
    CServer();
    
    pid_t cserver_getppid();
    pid_t cserver_getpid();

    pid_t cserver_setppid(pid_t pid);
    pid_t cserver_setpid(pid_t ppid);
    void  cserver_setproctype(int type);
private:
    ProcessMsg processMsg;
    int procTitleLen;
    int processCount;
    bool stop;
};

#endif