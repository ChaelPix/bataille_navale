#pragma once
#ifndef _TCPServer
#define _TCPServer

#include "TCPWinsocksMaster.h"
#include <vector>
#include <queue>
#include <thread>

class TCPServer : public TCPWinsocksMaster
{
private:

    std::vector<thread> clientThreads;


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

