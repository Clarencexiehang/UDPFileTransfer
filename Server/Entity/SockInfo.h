#ifndef SERVER_SOCKINFO_H
#define SERVER_SOCKINFO_H


#include <arpa/inet.h>



class SockInfo{
public:
    struct sockaddr_in addr;     //绑定端口号
    int fd;                      //文件描述符
};

#endif //SERVER_SOCKINFO_H
