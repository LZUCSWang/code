#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "winsock2.h"
#include <cstdlib>
#pragma comment(lib, "ws2_32.lib") //引用库文件
using namespace std;

char recvBuf[100];
SOCKET sockConn;
/**
 * 在一个新的线程里面接收数据
 */
DWORD WINAPI Fun(LPVOID lpParamter)
{
    while (true)
    {
        memset(recvBuf, 0, sizeof(recvBuf));
        //      //接收数据
        recv(sockConn, recvBuf, sizeof(recvBuf), 0);
        printf("%s\n", recvBuf);
    }
    closesocket(sockConn);
}

int main()
{
    WSADATA wsaData;
    int port = 8888; //端口号
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("initialization failed");
        return 0;
    }

    //创建用于监听的套接字,即服务端的套接字
    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(port); // 1024以上的端口号
    /**
     * INADDR_ANY就是指定地址为0.0.0.0的地址，这个地址事实上表示不确定地址，或“所有地址”、“任意地址”。 一般来说，在各个系统中均定义成为0值。
     */
    addrSrv.sin_addr.S_un.S_addr = htons(INADDR_ANY);

    int retVal = bind(sockSrv, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN));
    if (retVal == SOCKET_ERROR)
    {
        printf("connection failed:%d\n", WSAGetLastError());
        return 0;
    }

    if (listen(sockSrv, 10) == SOCKET_ERROR)
    {
        printf("Listening failed:%d", WSAGetLastError());
        return 0;
    }

    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);

    while (1)
    {
        //等待客户请求到来
        sockConn = accept(sockSrv, (SOCKADDR *)&addrClient, &len);
        if (sockConn == SOCKET_ERROR)
        {
            printf("Wait request failed:%d", WSAGetLastError());
            break;
        }

        printf("The IP of the client is:[%s]\n", inet_ntoa(addrClient.sin_addr));

        //发送数据
        char sendbuf[] = "Hello, I'm a server. Let's chat together";
        int iSend = send(sockConn, sendbuf, sizeof(sendbuf), 0);
        if (iSend == SOCKET_ERROR)
        {
            printf("fail in send");
            break;
        }

        HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
        CloseHandle(hThread);
    }

    closesocket(sockSrv);
    WSACleanup();
    system("pause");
    return 0;
}
