#include "TCPClient.h"

TCPClient::TCPClient(const std::string& serverIP, ushort serverPORT) : TCPWinsocksMaster(serverPORT), serverIP(serverIP)
{
	init();
}

std::string TCPClient::processGameMessage(const std::string& message)
{
    return std::string();
}

void TCPClient::init()
{
	connectToServer();
}

void TCPClient::connectToServer()
{
    adr_server.sin_family = AF_INET;
    adr_server.sin_port = htons(serverPORT);

    std::cout << "\nClient :" << idSocket;
    inet_pton(AF_INET, serverIP.c_str(), &adr_server.sin_addr);
    if (connect(idSocket, (struct sockaddr*)&adr_server, sizeof(adr_server)) < 0) {
        throw std::runtime_error("Connect to Server Failed");
    }
}


