#include "TCPServer.h"

TCPServer::TCPServer(ushort serverPORT) : TCPWinsocksMaster(serverPORT)
{
    init();
}

void TCPServer::init()
{
    bindAndListen();
}

void TCPServer::setupAddress()
{
    memset(&adr_server, 0, sizeof(adr_server));

    adr_server.sin_family = AF_INET;
    adr_server.sin_port = htons(serverPORT);
    adr_server.sin_addr.s_addr = htonl(INADDR_ANY);
}

void TCPServer::bindAndListen()
{
    setupAddress();

    if (bind(idSocket, (struct sockaddr*)&adr_server, sizeof(adr_server)) == SOCKET_ERROR) {
        throw std::runtime_error("Bind Failed");
    }

    if (listen(idSocket, 1) == SOCKET_ERROR) {
        throw std::runtime_error("Listene Failed");
    }
}

void TCPServer::acceptClients()
{
    addr_len = sizeof(adr_client);
    idClient = accept(idSocket, (struct sockaddr*)&adr_client, &addr_len);
}


void TCPServer::handleClient(SOCKET clientSocket)
{

}
