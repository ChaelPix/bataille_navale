#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <string>
#include "BsBDD.h"

class CoreGame;

class TCPClient {
private:
    WSADATA WSAData;
    SOCKET serverSocket;
    SOCKADDR_IN serverAddr;
    bool isConnected;
    CoreGame* __Coregame;
public:
    TCPClient();
    ~TCPClient();
    bool connectToServer(const std::string& address, int port);
    bool sendMessage(const std::string& message);
    std::string receiveMessage();
    void closeConnection();
};

#endif // TCPCLIENT_H
