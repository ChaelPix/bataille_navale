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
#include <condition_variable>
#include "SessionManager.h"

class TCPServer : public TCPWinsocksMaster
{
protected: 
    bool isServerOn;
    struct sockaddr_in adr_client;
    unsigned int addr_len;

    std::thread listenerThread;
    std::thread receiveThread;

    std::thread matchThread;

    std::vector<int> idsClients;

    std::queue<int> matchmakingQueue;

    std::mutex matchmakingMutex;
    std::condition_variable cvMatchmaking;
    std::unordered_map<int, std::thread> gameThreads;

    virtual void gameSession(int client1, int client2, bool isFirstPlayerToPlay);
    virtual std::string processGameMessage(const std::string& message);
    virtual void matchClientsForGame();

    SessionManager sessionManager;
public:

    virtual void init() override;
    TCPServer(ushort portNum);
    void closeSocket() override;
    std::string receiveMessageFromClient(int clientId);
    virtual void acceptClients();
    bool isSocketActive(int clientSocket);
protected:
    void setupAddress();
    void bindAndListen();
    void closeClientSocket(int clientSocket);
    bool isClientConnected(int clientId);

};

#endif

