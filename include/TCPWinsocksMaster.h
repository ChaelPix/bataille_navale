#pragma once
#ifndef _TCPWinsock
#define _TCPWinsock

#include <sys/types.h>
#include <sys/socket.h> // socket, recv, send
#include <netinet/in.h> // sockaddr_in, htonl
#include <arpa/inet.h>  // inet_addr
#include <unistd.h>     // close
#include <cstring> 
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
    int idSocket;
    struct sockaddr_in adr_server;
    ushort serverPORT;

    char trame_lect[DIMMAX + 1];

    void initializeWinsock();
    virtual void createSocket();
    virtual void init() = 0;
   

public:

    TCPWinsocksMaster(uint serverPORT);
    ~TCPWinsocksMaster();

    const int getIdSocket();

    void sendMessage(int idTarget, std::string msg);
    std::string sendAndReceiveMsg(int idTarget, const std::string& msg);
    void sendMessage(std::string msg);
    virtual std::string receiveMessage();

    virtual void closeSocket();
};

#endif