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
private: 
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

    void matchClientsForGame();
    void gameSession(SOCKET client1, SOCKET client2);

    bool isServerOn;
    void init() override;

    std::string processGameMessage(const std::string& message);

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

