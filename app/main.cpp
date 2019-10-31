#include <bits/stdc++.h>
#include "conf.h"
#include "clog.h"
#include "timeTools.h"
#include "cserver.h"
#include "unistd.h"
#include "csocket.h"
#include "process.h"

using namespace std;

extern char ** environ;

CConfigKV *g_conf = nullptr;
CLog      *g_log  = nullptr;
CServer   *g_cserver = nullptr;

int g_os_argc = 0;
int g_arg_len = 0;
char **g_os_argv = nullptr;
char **g_os_old_argv = nullptr;

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

static void serverWorkProcess() 
{
    string strWorkNum = g_conf->get_conf("work_proc_num");
    int worknum = strWorkNum.empty() ? 1 : StringTools::StringToInt(strWorkNum);
    workProcessLoop();
}

int main(int argc, char *const *argv)
{
    do {
        g_conf = new CConfigKV();
        g_conf->init();
        g_log  = new CLog();

        if (g_conf == nullptr || g_log == nullptr) {
            INFO_LOG("g_conf or g_log fail");
            break;
        }
        INFO_LOG("Success init log and config");

        // 以守护进程的方式运行
        // DEBUG_LOG("before init_deamon() pid = %d ppid = %d", getpid(), getppid());
        // int ret_deamon = init_deamon();
        // if (ret_deamon == 1) {
        //     INFO_LOG("father process exit");
        //     break;
        // } else if(ret_deamon == -1) {
        //     ERR_LOG("init_deamon() fail exit()");
        //     break;
        // }
        // DEBUG_LOG("after init_deamon() pid = %d ppid = %d", getpid(), getppid());
        
        // 初始化服务
        g_cserver = new CServer();
        if (g_cserver == nullptr) {
            ERR_LOG("init g_cserver fail");
            break;
        }
        INFO_LOG("Success init server pid = %d", g_cserver->cserver_getppid());
        
        // 迁移环境变量和命令行参数
        g_os_argc = argc;
        g_os_argv = (char**) argv;
        g_os_old_argv = (char**) argv;
        moveArgv();
        moveGlobalEnviron();
        setproctitle(argv, SERVER_MASTER);

        // 事件循环
        serverWorkProcess();
        while (true);

    } while(false);

    INFO_LOG("sever success to finish");

    delete g_log;
    delete g_conf;
    delete g_cserver;
    return 0;
}
