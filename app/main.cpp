#include <bits/stdc++.h>
#include "conf.h"
#include "clog.h"
#include "timeTools.h"
#include "cserver.h"
#include "unistd.h"

using namespace std;

extern char ** environ;

CConfigKV *g_conf = nullptr;
CLog      *g_log  = nullptr;
CServer   *g_cserver = nullptr;

int g_os_argc = 0;
int g_arg_len = 0;
char **g_os_argv = nullptr;

int g_env_len = 0;
char **g_env_mem = nullptr;

static void moveArgv()
{
    for (int i = 0; i < g_os_argc; i++ ) {
        g_arg_len += strlen(g_os_argv[i]) + 1;
    }
    char *new_argv = new char[g_arg_len];
    char *ptmp = new_argv;
    for (int i = 0; i < g_os_argc; i++ ) {
        int size = strlen(g_os_argv[i]) + 1;
        strcpy(ptmp, g_os_argv[i]);
        ptmp += size;
    }
    g_os_argv = (char **)new_argv;
}

static void moveGlobalEnviron()
{   
    for (int i = 0; environ[i]; i++ ) {
        g_env_len += strlen(environ[i]) + 1;
    }
    char *new_env_mem = new char[g_env_len];
    char *ptmp = new_env_mem;
    for (int i = 0; environ[i]; i++) {
        size_t size = strlen(environ[i]) + 1;
        strcpy(ptmp, environ[i]);
        environ[i] = ptmp;
        ptmp += size;
    }
}

void setproctitle(char *const *argv, const char *title)
{
    size_t titleLen = strlen(title);
    size_t maxTitleLen = g_arg_len + g_env_len;
    if (titleLen + 1 <= maxTitleLen) {
        char *ptmp = argv[0];
        strcpy(ptmp, title);
        ptmp += titleLen;
        memset(ptmp, 0, maxTitleLen - titleLen);
    } else {
        WARN_LOG("set process title fail");
    }
}

int main(int argc, char *const *argv)
{
    do {
        g_conf = new CConfigKV();
        g_conf->init();
        g_log  = new CLog();

        if (g_conf == nullptr || g_log == nullptr) {
            // 日志模块和配置模块都失败就没救了...
            break;
        }
        INFO_LOG("Success init log and config");
        DEBUG_LOG("before init_deamon() pid = %d ppid = %d", getpid(), getppid());
        
        int ret_deamon = init_deamon();
        if (ret_deamon == 1) {
            DEBUG_LOG("father process exit()");
            break;
        } else if(ret_deamon == -1) {
            ERR_LOG("init_deamon() fail exit()");
            break;
        }

        DEBUG_LOG("after init_deamon() pid = %d ppid = %d", getpid(), getppid());
        g_cserver = new CServer();
        if (g_cserver == nullptr) {
            ERR_LOG("init g_cserver fail");
            break;
        }
        INFO_LOG("Success init server pid = %d", g_cserver->cserver_getppid());
        
        g_os_argc = argc;
        g_os_argv = (char**) argv;
        moveArgv();
        moveGlobalEnviron();
        setproctitle(argv, SERVER_MASTER);

        while (true);

    } while(false);

    return 0;
}
