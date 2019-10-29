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

extern CLog      *g_log;
extern CConfigKV *g_conf;

using std::vector;
using std::string;

class CSocket {
public:

    static int socketBind(int port);
    static void simpleSocketLoop();
private:

};

#endif