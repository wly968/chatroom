#include "Client.h"
void Client::Initialize(){
    system("chcp 65001 > nul");
    WSAStartup(MAKEWORD(2, 2), &wsa);
    client = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("客户端初始化完成\n");
}

void Client::Connect(){
    if (connect(client, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        printf("连接失败，错误码: %d\n", WSAGetLastError());
        closesocket(client);
        WSACleanup();
        system("pause");
    }
    printf("连接成功！\n");
}

string Client::Receive(){
    char buf[100] = {0};
    int len = recv(client, buf, sizeof(buf) - 1, 0);
    if (len > 0) {
        buf[len] = '\0';
    }
    return string(buf);
}

void Client::Send(const char* msg){
    send(client, msg, strlen(msg), 0);
}

void Client::Close(){
    closesocket(client);
    WSACleanup();
    printf("客户端已关闭。按 Enter 退出...\n");
    getchar();
}

SOCKET Client::get(){
    return client;
}