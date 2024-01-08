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
#include "SessionManager.h"

class TCPServer : public TCPWinsocksMaster
{
protected: 
    bool isServerOn;
    struct sockaddr_in adr_client;
    int addr_len;

protected:
    std::thread listenerThread;
    std::thread matchThread;

    std::thread receiveThread;

    std::vector<SOCKET> idsClients;

    std::queue<SOCKET> matchmakingQueue;

    std::mutex matchmakingMutex;
    std::condition_variable cvMatchmaking;
    std::unordered_map<SOCKET, std::thread> gameThreads;

    virtual void gameSession(SOCKET client1, SOCKET client2, bool isFirstPlayerToPlay);
    virtual std::string processGameMessage(const std::string& message);
    virtual void matchClientsForGame();

    SessionManager sessionManager;
public:

    virtual void init() override;
    TCPServer(ushort portNum);
    void closeSocket() override;
    std::string receiveMessageFromClient(SOCKET clientId);
    virtual void acceptClients();
    bool isSocketActive(SOCKET clientSocket);
protected:
    void setupAddress();
    void bindAndListen();
    void closeClientSocket(SOCKET clientSocket);
    bool isClientConnected(SOCKET clientId);

};

#endif

