#ifndef _C_SOCKET_H_
#define _C_SOCKET_H_

#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>

#include "stringTools.h"
#include "clog.h"
#include "conf.h"
#include "cserver.h"

extern CLog      *g_log;
extern CConfigKV *g_conf;
extern CServer   *g_cserver;

using std::vector;
using std::string;

class CSocket {
public:

    static int socketBind(int port);
    static void simpleSocketLoop();
private:
    
};

// 测试epoll的系列函数

void doEpoll(vector<int> fds);

void handleAccept(int epollfd, int listenfd);

void handleEvents(int epollfd, struct epoll_event *events, int num, int listenfd, char* buf);

void doRead(int epollfd, int fd, char* buf);

void doWrite(int epollfd, int fd, char* buf);

void addEvent(int epollfd, int fd, int state);

void deleteEvent(int epollfd, int fd, int state);

void modifyEvent(int epollfd, int fd, int state);

#endif