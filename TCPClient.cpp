#include "TCPClient.h"

TCPClient::TCPClient(const std::string& serverIP, ushort serverPORT) : TCPWinsocksMaster(), serverIP(serverIP), serverPORT(serverPORT)
{
	init();
}

void TCPClient::init()
{
	connectToServer();
}

void TCPClient::connectToServer()
{
    adr_serveur.sin_family = AF_INET;
    adr_serveur.sin_port = htons(serverPORT);

    inet_pton(AF_INET, serverIP.c_str(), &adr_serveur.sin_addr);
    if (connect(idSocket, (struct sockaddr*)&adr_serveur, sizeof(adr_serveur)) < 0) {
        throw std::runtime_error("Connect to Server Failed");
    }
}


