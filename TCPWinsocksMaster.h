#pragma once
#ifndef _TCPWinsock
#define _TCPWinsock

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdexcept>
#include <string>
#include <iostream>

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

const ushort DIMMAX = 2048;

class TCPWinsocksMaster
{
protected:
    WSADATA wsaData;
    SOCKET idSocket;
    struct sockaddr_in adr_server;
    ushort serverPORT;

    char trame_lect[DIMMAX + 1];

    void initializeWinsock();
    virtual void createSocket();
    virtual void init() = 0;
   

public:

    TCPWinsocksMaster(uint serverPORT);
    ~TCPWinsocksMaster();

    const SOCKET getIdSocket();

    void sendMessage(SOCKET idTarget, std::string msg);
    std::string sendAndReceiveMsg(SOCKET idTarget, const std::string& msg);
    void sendMessage(std::string msg);
    virtual std::string receiveMessage();

    virtual void closeSocket();
};

#endif