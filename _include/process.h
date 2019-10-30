#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "cserver.h"
#include "csocket.h"
#include "define.h"
#include "conf.h"
#include "clog.h"

#define PROCESS_TYPE_DEFAULT 0
#define PROCESS_TYPE_MASTER  1
#define PROCESS_TYPE_WORKER  2

extern CLog    *g_log;
extern CServer *g_cserver;
extern char    **g_os_old_argv;
extern int     g_arg_len;
extern int     g_env_len;

using std::vector;

int init_deamon();

void setproctitle(char *const *argv, const char *title);

void workProcessLoop();

#endif