#ifndef _SERVER_H_
#define _SERVER_H_

#include "process.h"
#include "unistd.h"
#include "clog.h"

extern CLog *g_log;

class CServer {
public:
    CServer();
    
    pid_t cserver_getppid();
    pid_t cserver_getpid();

    pid_t cserver_setppid(pid_t pid);
    pid_t cserver_setpid(pid_t ppid);
private:
    ProcessMsg processMsg;
    int procTitleLen;
};

#endif