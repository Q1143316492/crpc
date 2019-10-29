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