
#include <stdio.h>
#include <string.h>
#include "stdafx.h"
#include "udp.h"

int myudp::socket_send(const char * ip, const char * msg ,int len)
{
    struct sockaddr_in addr;//建立并填充地址结构
    memset(&addr,0,sizeof(addr));//初始化
    addr.sin_family = AF_INET;//使用的协议簇
    addr.sin_port = htons(8080);//填充端口号
    addr.sin_addr.s_addr = inet_addr(ip);//设置IP地址

        //调用C语言的底层发送函数(sendto) 函数返回值表示 实际发送的数据量
        size_t rc = sendto(s,msg,len,0,(struct sockaddr *)&addr,sizeof(addr));
        printf("send success!\n");

    return 1;
}


int myudp::socket_recv(char * r_msg , int len, char *stcip)
{
        //来自发送方的地址结构
        struct sockaddr_in sen_addr;
        memset(&sen_addr,0,sizeof(sen_addr));

#ifdef MYLINUX
        socklen_t sen_addr_len;
#else
        int sen_addr_len;
#endif


        sen_addr_len = sizeof(sen_addr);
        //接收
        //接收缓冲区
        //char recv_buf[1024] = {0};
        size_t rc;

        memset(r_msg,0,len);

            //调用C语言的底层接收函数(recvfrom) 函数返回值表示 实际接收的数据量
            rc = recvfrom(s,r_msg,len,0,(struct sockaddr *)&sen_addr,&sen_addr_len);
           //printf("recvive data %s : %s\n",inet_ntoa(sen_addr.sin_addr),r_msg);
            if (stcip)
           strcpy(stcip,inet_ntoa(sen_addr.sin_addr));
    return rc;
}
myudp::myudp()
{
#ifndef MYLINUX
    //初始化版本号(socket)
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2),&wsa);
#endif
    //建立SOCKET(套接字)

    s = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP); //调用函数
    //AF_INET：表示使用的是TCP/IP协议簇
    //SOCK_DGRAM：表示使用的是UDP
}

myudp::myudp(const myudp &it)
{
#ifndef MYLINUX
    //初始化版本号(socket)
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2),&wsa);
#endif
    //建立SOCKET(套接字)

    this->s = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP); //调用函数
    //AF_INET：表示使用的是TCP/IP协议簇
    //SOCK_DGRAM：表示使用的是UDP

}

myudp::~myudp()
{
#ifdef MYLINUX
    close(s);
#else
    closesocket(s);//发送完成后，将套接字关闭
    WSACleanup();//清除初始化版本号时所分配的资源
#endif
}

int myudp::socket_bind(short port)
{

    struct sockaddr_in addr;//建立并填充地址结构
    memset(&addr,0,sizeof(addr));//初始化
    addr.sin_family = AF_INET;//使用的协议簇
    addr.sin_port = htons(port);//填充端口号
    addr.sin_addr.s_addr = htonl(INADDR_ANY);//如果只作为接收方的话，就不需要指定IP地址，所有的ip都能发送

    //将地址结构和套接字进行绑定
   //绑定的意义在于，操作系统要避免对于操作系统来讲，一定要避免两个程序同时绑定到一个端口。
    return ( bind(s,(struct sockaddr *)&addr,sizeof(addr)) != -1);
}
