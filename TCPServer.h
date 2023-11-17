#pragma once
#ifndef _TCPServer
#define _TCPServer

#include "TCPWinsocksMaster.h"
#include <thread>

class TCPServer : public TCPWinsocksMaster
{
private: 
    struct sockaddr_in adr_client;
    int addr_len;
    uint idClient;

    std::thread listenerThread;
    bool isServerOn;

public:
    /*
    ushort portNum
    */
    TCPServer(ushort portNum);
    void init() override;
    void handleClient(SOCKET clientSocket);
    void closeSocket() override;

private:
    void setupAddress();
    void bindAndListen();
    void acceptClients();
    void closeClientSocket(SOCKET clientSocket);

    
};

#endif

