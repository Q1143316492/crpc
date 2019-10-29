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