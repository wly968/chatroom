#include "Server.h"
#include <thread>
#include <cstring>
#include <vector>
#include <mutex>

vector<SOCKET> clients;
mutex clientsMutex;

void AddClient(SOCKET cli){
    lock_guard<mutex> lock(clientsMutex);
    clients.push_back(cli);
}

void RemoveClient(SOCKET cli){
    lock_guard<mutex> lock(clientsMutex);
    for (int i = 0; i < clients.size() ; i++){
        if (clients[i] == cli){
            clients.erase(clients.begin()+i);
        }
    }
}
void Broadcast(string msg,SOCKET sender,string username){
    lock_guard<mutex> lock(clientsMutex);
    for (SOCKET s : clients) {
        if (s != sender) {
            send(s, username.c_str(), username.size(), 0);
            send(s, msg.c_str(), msg.size(), 0);
        }
    }
}

void HandleClient(SOCKET client){
    char buf1[1024];
    printf("[线程 %d] 客户端已连接\n", GetCurrentThreadId());
    int len = recv(client,buf1,sizeof(buf1)-1,0);
    buf1[len] = '\0';
    string username = string(buf1);

    char buf[1024];
    while (1){
        int len = recv(client,buf,sizeof(buf)-1,0);
        if (len <= 0) {
            printf("[线程 %d] 客户端断开\n", GetCurrentThreadId());
            break;
        }
        buf[len] = '\0';
        printf("收到来自%s: %s\n",username.c_str(), buf);
        Broadcast(string(buf),client,username);
    }
    RemoveClient(client);
    closesocket(client);
    printf("[线程 %d] 线程结束\n", GetCurrentThreadId());
}

int main(){
    system("chcp 65001 > nul");
    Server server;
    server.Initialize();
    server.Listen();
    
    while (1){
        SOCKET cli = server.Accept();
        if (cli == INVALID_SOCKET) {
            printf("accept 失败\n");
            break;
        }
        AddClient(cli);
        thread t(HandleClient,cli);
        t.detach();
        cout<<"当前连接数："<<clients.size()<<endl;
    }

    server.Close();
}