#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdexcept>

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

class TCPWinsocksMaster
{
protected:
    WSADATA wsaData;
    SOCKET idSocket;
    struct sockaddr_in adr_serveur;

    void initializeWinsock();
    virtual void createSocket();
    void closeSocket();

public:

    TCPWinsocksMaster();
    virtual ~TCPWinsocksMaster();
    virtual void start() = 0;

    const SOCKET getIdSocket();
    
};