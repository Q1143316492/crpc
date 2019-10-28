#include "cserver.h"

CServer::CServer() {
    processMsg.pid = getpid();
    processMsg.ppid = getppid();
    procTitleLen = 0;
}

pid_t CServer::cserver_getppid()
{
    return this->processMsg.pid;
}

pid_t CServer::cserver_getpid()
{
    return this->processMsg.ppid;
}