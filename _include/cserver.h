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
private:
    ProcessMsg processMsg;
    int procTitleLen;
};

#endif