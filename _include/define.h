#ifndef _DEFINE_H_
#define _DEFINE_H_

// 日志宏
#define NO_BUG_LOG_CORE_ERR          5    //严重错误 【error】
#define NO_BUG_LOG_ERR               4    //错误 【error】
#define NO_BUG_LOG_WARN              3    //警告 【warn】
#define NO_BUG_LOG_NOTICE            2    //注意 【notice】
#define NO_BUG_LOG_INFO              1    //信息 【info】
#define NO_BUG_LOG_DEBUG             0    //调试 【debug】

#define STR_NO_BUG_LOG_CORE_ERR      "CORE_ERR"
#define STR_NO_BUG_LOG_ERR           "ERR"      //错误 【error】
#define STR_NO_BUG_LOG_WARN          "WARN"     //警告 【warn】
#define STR_NO_BUG_LOG_NOTICE        "NOTICE"   //注意 【notice】
#define STR_NO_BUG_LOG_INFO          "INFO"     //信息 【info】
#define STR_NO_BUG_LOG_DEBUG         "DEBUG"    //调试 【debug】

// 进程名字
#define SERVER_MASTER "cserver_master"
#define SERVER_WORKER "cserver_worker"

// process type master or worker
#define PROC_TYPE_UNDEFINE  0
#define MASTER_PROCESS      1
#define WORKER_PROCESS      2

// socket listen queue size
#define LISTENQ 5

// epoll
#define EPOLL_BUF_MAXSIZE     1024
#define EPOLL_INIT_FDSIZE     1000
#define EPOLL_EVENT_SIZE      100

#endif