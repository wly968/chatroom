#include <iostream>
#include <winsock2.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

class Server{
    private:
        WSADATA wsa;
        SOCKET server;
        struct sockaddr_in addr;
        SOCKET client;
    public:
        void Initialize();
        void Listen();
        SOCKET Accept();
        string Receive();
        void Send(const char* msg);
        void Close();
};