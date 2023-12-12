#pragma once
#ifndef _TCPClient
#define _TCPClient

#include "TCPWinsocksMaster.h"
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

class TCPClient : public TCPWinsocksMaster
{

private:
    std::string serverIP;
    std::queue<std::string> messageQueue;
    std::mutex queueMutex;
    std::condition_variable cv;
    bool receiving = true;
    std::thread receiveThread;

    void connectToServer();
    void init() override;
    void receiveMessages();

public:

    TCPClient(const std::string& ipServeur, ushort portServeur);
    ~TCPClient();

    void startReceiving();
    std::string getMessage();
    void stopReceiving();
};

#endif

