#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib") //引用库文件
using namespace std;

int main()
{
    //加载套接字
    WSADATA wsaData;
    char buff[1024];
    memset(buff, 0, sizeof(buff));

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("initng Winsock failed");
        return 0;
    }

    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(8888);                        //端口号
    addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // IP地址

    //创建套接字
    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
    if (SOCKET_ERROR == sockClient)
    {
        printf("Socket() error:%d", WSAGetLastError());
        return 0;
    }

    //向服务器发出连接请求
    if (connect(sockClient, (struct sockaddr *)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET)
    {
        printf("connection failed:%d", WSAGetLastError());
        return 0;
    }
    else
    {
        //接收数据
        recv(sockClient, buff, sizeof(buff), 0);
        printf("%s\n", buff);
    }

    //发送数据
    char buffs[] = "Now let's start chatting";
    send(sockClient, buffs, sizeof(buffs), 0);
    //不断输入，然后发送
    while (true)
    {
        cin >> buffs;
        send(sockClient, buffs, sizeof(buffs), 0);
    }

    //关闭套接字
    closesocket(sockClient);
    WSACleanup();    //释放初始化Ws2_32.dll所分配的资源。
    system("pause"); //让屏幕暂留
    return 0;
}