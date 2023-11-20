#pragma once
#ifndef _TCPServer
#define _TCPServer

#include "TCPWinsocksMaster.h"
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <unordered_map>
#include <chrono>

class TCPServer : public TCPWinsocksMaster
{
protected: 
    bool isServerOn;
    struct sockaddr_in adr_client;
    int addr_len;

    std::thread listenerThread;
    std::thread receiveThread;

    std::thread matchThread;

    std::vector<SOCKET> idsClients;

    std::queue<SOCKET> matchmakingQueue;

    std::mutex matchmakingMutex;
    std::condition_variable cvMatchmaking;
    std::unordered_map<SOCKET, std::thread> gameThreads;

    virtual void gameSession(SOCKET client1, SOCKET client2);
    virtual std::string processGameMessage(const std::string& message);
    virtual void matchClientsForGame();

public:

    virtual void init() override;
    TCPServer(ushort portNum);
    void closeSocket() override;
    std::string receiveMessageFromClient(SOCKET clientId);
    virtual void acceptClients();

protected:
    void setupAddress();
    void bindAndListen();
    void closeClientSocket(SOCKET clientSocket);
    
};

#endif

