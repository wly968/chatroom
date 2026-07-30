#include <iostream>
#include <winsock2.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

class Client{
    private:
        WSADATA wsa;
        struct sockaddr_in addr;
        SOCKET client;
    public:
        void Initialize();
        void Connect();
        string Receive();
        void Send(const char* msg);
        void Close();
        SOCKET get();
};