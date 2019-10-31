#ifndef _EVENT_POOLS_H_
#define _EVENT_POOLS_H_

#include <bits/stdc++.h>

using std::string;
using std::unordered_map;

struct Connection;

typedef void readHandler(Connection con);
typedef void writeHandler(Connection con);

struct Connection {
    int fd;
    u_int mask;
    readHandler  *rfileProc;
    writeHandler *wfileProc;
};


struct EventPools {
    unordered_map<int, Connection> connectPools;
};

void addEventToLoops(int fd, Connection *con);

void delEventFromLoops(int fd);

#endif