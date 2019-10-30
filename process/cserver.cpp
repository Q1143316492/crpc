#include "cserver.h"

CServer::CServer() {
    processMsg.pid = getpid();
    processMsg.ppid = getppid();
    processCount = 1;
    procTitleLen = 0;
    stop = false;
}

pid_t CServer::cserver_getppid()
{
    return this->processMsg.pid;
}

pid_t CServer::cserver_getpid()
{
    return this->processMsg.ppid;
}

pid_t CServer::cserver_setppid(pid_t pid)
{
    this->processMsg.pid = pid;
}

pid_t CServer::cserver_setpid(pid_t ppid)
{
    this->processMsg.ppid = ppid;
}

void  CServer::cserver_setproctype(int type)
{
    this->processMsg.procType = type;
}