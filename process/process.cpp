#include "process.h"

int init_deamon()
{
    switch (fork()) 
    {
    case -1:
        CORE_ERR_LOG("deamon init fork() fail");
        return -1;
    case 0:
        // son process
        break;
    default:
        return 1;
    }
    INFO_LOG("init_deamon() pid = %d ppid = %d", getpid(), getppid());
    if (setsid() == -1)  
    {
        CORE_ERR_LOG("deamon init setsid() fail");
        return -1;
    }
    umask(0); 
    int fd = open("/dev/null", O_RDWR);
    if (fd == -1) 
    {
        CORE_ERR_LOG("deamon init open /dev/null fail");
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        CORE_ERR_LOG("deamon init dup2(STDIN) fail");  
        return -1;
    }
    if (dup2(fd, STDOUT_FILENO) == -1) 
    {
        CORE_ERR_LOG("deamon init dup2(STDOUT) fail");
        return -1;
    }
    if (fd > STDERR_FILENO)
     {
        if (close(fd) == -1)
        {
            CORE_ERR_LOG("deamon init close(fd) fail");
            return -1;
        }
    }
    return 0;
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

void workProcessLoop()
{
    setproctitle(g_os_old_argv, SERVER_WORKER);
    
    string strPort = g_conf->get_conf("port");
    vector<string> vecPort = StringTools::splitString(strPort, ';');
    
    vector<int> vecListenFds;
    for (size_t i = 0; i < vecPort.size(); i++ ) {
        int listenfd = CSocket::socketBind(StringTools::StringToInt(vecPort[i].c_str()));
        int ret = listen(listenfd, LISTENQ);
        if (ret == -1) {
            WARN_LOG("fail to listen port %d", vecPort[i].c_str());
        } else {
            DEBUG_LOG("prepare listen fd %d", listenfd);
            vecListenFds.push_back(listenfd);
        }
    }
    while (!g_cserver->isStop()) {
        
        doEpoll(vecListenFds);
        
    }
}