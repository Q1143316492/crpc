#include "csocket.h"

int CSocket::socketBind(int port)
{
    int listenfd = 0;
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(port);    

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("socket error");
        WARN_LOG("socket error");
        return -1;
    }
    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind error: ");
        WARN_LOG("bind error: ");
        return -1;
    }
    return listenfd;
}

void CSocket::simpleSocketLoop()
{
    string strPort = g_conf->get_conf("port");
    vector<string> vecPort = StringTools::splitString(strPort, ';');
    if (vecPort.size() == 0) {
        WARN_LOG("without out port to listen in config");
        return ;
    }
    int listenfd = CSocket::socketBind(StringTools::StringToInt(vecPort[0]));
    if (listenfd == -1) {
        WARN_LOG("fail to listen port : %s", vecPort[0].c_str());
        return ;
    }
    int ret = listen(listenfd, 5);
    if (ret == -1) {
        WARN_LOG("listen fail port %s", vecPort[0].c_str());
        return ;
    }
    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof( client );

    const int BUF_SIZE = 1024;
    while (true) {
        int connfd = accept(listenfd, (struct sockaddr*)&client, &client_addrlength);
        if (connfd >= 0) {
            char buffer[ BUF_SIZE ];
            int ret = recv( connfd, buffer, BUF_SIZE - 1, 0 );
            std::cout << buffer << std::endl;
            write(connfd, buffer, strlen(buffer));
        } else {
            WARN_LOG("accept() fail. errno = %d", errno);
        }
        close(connfd);
    }
    close(listenfd);
}

void doEpoll(vector<int> &fds)
{
    int epollfd;
    struct epoll_event events[EPOLL_EVENT_SIZE];
    int ret;
    char buf[EPOLL_BUF_MAXSIZE];
    memset(buf, 0, EPOLL_BUF_MAXSIZE);
    epollfd =  epoll_create(EPOLL_INIT_FDSIZE);

    for (size_t i = 0; i < fds.size(); i++ ) {
        addEvent(epollfd, fds[i], EPOLLIN);
    }
    while(true) {
        ret = epoll_wait(epollfd, events, EPOLL_EVENT_SIZE, -1);
        handle_events(epollfd, events, ret, listenfd, buf);
    }
    close(epollfd);
}

void handle_accept(int epollfd, int listenfd) {
    int clifd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    clifd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddrlen);
    if(clifd == -1) {
        perror("accpet error:");
    } else {
        printf("accept a new client: %s : %d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
        add_event(epollfd, clifd, EPOLLIN);
    }
}

void handle_events(int epollfd, struct epoll_event *events, int num,
                   int listenfd, char* buf) {
    for(int i = 0; i < num; i++ ) {
        int fd = events[i].data.fd;
        if((fd == listenfd) && (events[i].events & EPOLLIN)) {
            handle_accept(epollfd, listenfd);
        } else if(events[i].events & EPOLLIN) {
            doRead(epollfd, fd, buf);
        } else if(events[i].events & EPOLLOUT) {
            doWrite(epollfd, fd, buf);
        }
    }
}

void doRead(int epollfd, int fd, char* buf) {
    int nread = read(fd, buf, MAXSIZE);
    if(nread == -1) {
        perror("read error:");
        close(fd);
        deleteEvent(epollfd, fd, EPOLLIN);
    }
    else if(nread == 0) {
        fprintf(stderr, "client close.\n");
        close(fd);
        deleteEvent(epollfd, fd, EPOLLIN);
    } else {
        printf("read message is: %s \n", buf);
        modifyEvent(epollfd, fd, EPOLLOUT);
    }
}

void doWrite(int epollfd, int fd, char* buf) {
    int nwrite = write(fd, buf, strlen(buf));
    if(nwrite == -1) {
        perror("write error: ");
        close(fd);
        deleteEvent(epollfd, fd, EPOLLOUT);
    } else {
        modifyEvent(epollfd, fd, EPOLLIN);
    }
    memset(buf, 0, MAXSIZE);
}

void addEvent(int epollfd, int fd, int state) {
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

void deleteEvent(int epollfd, int fd, int state) {
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

void modifyEvent(int epollfd, int fd, int state) {
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}