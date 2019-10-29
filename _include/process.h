#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "clog.h"

#define PROCESS_TYPE_DEFAULT 0
#define PROCESS_TYPE_MASTER  1
#define PROCESS_TYPE_WORKER  2

typedef struct ProcessMessage {
    pid_t pid;
    pid_t ppid;
    u_int procType;
} ProcessMsg;

extern CLog    *g_log;

int init_deamon();


#endif