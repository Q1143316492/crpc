#define _EVENT_LOOP_H_
#define _EVENT_LOOP_H_

struct Connection {
    int fd;
    FileEvent event;
};

struct FileEvent {
    u_int mask;
    readHandler  *rfileProc;
    writeHandler *rfileProc;
};

typedef void readHandler(Connection con);
typedef void writeHandler(Connection con);

class EventLoop {
public:

private:

};

#endif