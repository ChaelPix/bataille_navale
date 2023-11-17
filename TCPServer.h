#pragma once
#ifndef _TCPServer
#define _TCPServer

#include "TCPWinsocksMaster.h"
#include <thread>
#include <vector>

class TCPServer : public TCPWinsocksMaster
{
private: 
    struct sockaddr_in adr_client;
    int addr_len;

    std::thread listenerThread;
    std::thread receiveThread;
    std::vector<SOCKET> idsClients;
    bool isServerOn;
    void init() override;

public:

    TCPServer(ushort portNum);
    virtual void handleClient(SOCKET clientSocket);
    void closeSocket() override;
    std::string receiveMessageFromClient(SOCKET clientId);

private:
    void setupAddress();
    void bindAndListen();
    void acceptClients();
    void closeClientSocket(SOCKET clientSocket);
    virtual void waitClientInstruction(SOCKET clientId);
    
};

#endif

