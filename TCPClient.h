#pragma once
#ifndef _TCPClient
#define _TCPClient

#include "TCPWinsocksMaster.h"

class TCPClient : public TCPWinsocksMaster
{

private:
    std::string serverIP;

    void connectToServer();
    void init() override;

public:

    TCPClient(const std::string& ip, ushort portNum);
};

#endif

