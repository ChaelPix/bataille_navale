#pragma once
#ifndef _TCPServer
#define _TCPServer

#include "TCPWinsocksMaster.h"


class TCPServer : public TCPWinsocksMaster
{
private: 
    struct sockaddr_in adr_client;
    int addr_len;
    uint idClient;

public:
    TCPServer(ushort portNum);

    void init() override;
    void handleClient(SOCKET clientSocket);

private:
    void setupAddress();
    void bindAndListen();
    void acceptClients();
};

#endif

