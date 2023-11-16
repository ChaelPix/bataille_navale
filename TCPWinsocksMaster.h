#pragma once
#ifndef _TCPWinsock
#define _TCPWinsock

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdexcept>
#include <string>

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

const ushort DIMMAX = 2048;

class TCPWinsocksMaster
{
protected:
    WSADATA wsaData;
    SOCKET idSocket;
    struct sockaddr_in adr_serveur;

    char trame_lect[DIMMAX + 1];

    void initializeWinsock();
    virtual void createSocket();
    void closeSocket();

public:

    TCPWinsocksMaster();
    ~TCPWinsocksMaster();
    virtual void init() = 0;

    const SOCKET getIdSocket();

    void sendMessage(SOCKET targetSocketId, std::string msg);
    std::string receiveMessage();
};

#endif