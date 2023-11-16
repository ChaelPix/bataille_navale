#pragma once
#ifndef _TCPClient
#define _TCPClient

#include "TCPWinsocksMaster.h"

class TCPClient : public TCPWinsocksMaster
{

private:
    std::string serverIP;

    void connectToServer();

public:

    TCPClient(const std::string& ip, ushort portNum);
    void init() override;
};

#endif

