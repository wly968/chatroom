#include "Server.h"

void Server::Initialize(){
    system("chcp 65001 > nul");
    WSAStartup(MAKEWORD(2, 2), &wsa);
    this->server = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;//IPV4
    addr.sin_port = htons(8888);//端口8888
    addr.sin_addr.s_addr = INADDR_ANY;//监听本机的所有网络接口
    bind(server, (struct sockaddr*)&addr, sizeof(addr));
    printf("服务器初始化成功\n");
}

void Server::Listen(){
    listen(this->server, 5);
    printf("服务器已启动，等待连接... (端口 8888)\n");
}

SOCKET Server::Accept(){
    client = accept(server, NULL, NULL);
    return client;
}

string Server::Receive(){
    char buf[100] = {0};
    int len = recv(client, buf, sizeof(buf) - 1, 0);
    if (len > 0) {
        buf[len] = '\0';
    }else{
        return string("#!*&%$^");
    }
    return string(buf);
}

void Server::Send(const char* msg){
    send(client, msg, strlen(msg), 0);
}

void Server::Close(){
    closesocket(client);
    closesocket(server);
    WSACleanup();
    system("pause");
}