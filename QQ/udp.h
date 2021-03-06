#ifndef UDP_H
#define UDP_H

#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib,"WS2_32.lib")


class myudp
{
private:
    SOCKET s;
public:
    myudp();
    myudp(const myudp &it);
    ~myudp();
    int socket_bind(short port);
    int socket_send(const char * ip, const char * msg ,int len);
    int socket_recv(char * r_msg , int len , char * stcip);
//明确的告诉编译器，这是一个C++中使用的文件，所以要将这个函数编译为C++的函数
};

#endif // UDP_H
