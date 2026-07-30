#include "Client.h"
#include <thread>
#include <mutex>

mutex mu;

void receive(SOCKET client){

    char buf1[1024],buf2[1024];
    while (1){
        string username,msg;
        int len = recv(client, buf1, sizeof(buf1) - 1, 0);
        if (len <= 0) break;
        buf1[len] = '\0';
        username = string(buf1);

        len = recv(client, buf2, sizeof(buf2) - 1, 0);
        if (len <= 0) break;
        buf2[len] = '\0';
        msg = string(buf2);

        lock_guard<mutex> lock(mu);
        printf("\r<%s>%s\n",username.c_str(), msg.c_str());
        fflush(stdout);//强制刷新标准输出的缓冲区
    }
    
}

int main(){
    system("chcp 65001 > nul");
    Client client;
    client.Initialize();
    client.Connect();

    thread t(receive,client.get());
    t.detach();

    string username;
    getline(cin,username);
    send(client.get(), username.c_str(), username.size(), 0);
    while (1){
        string input;
        getline(cin,input);
        client.Send(input.c_str());
    }

    client.Close();
}