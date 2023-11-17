#include "TCPServer.h"

TCPServer::TCPServer(ushort serverPORT) : TCPWinsocksMaster(serverPORT)
{
    init();
}

void TCPServer::init()
{
    bindAndListen();
    isServerOn = true;
    listenerThread = std::thread(&TCPServer::acceptClients, this);
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
    while (isServerOn) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(idSocket, &readfds);
        timeval timeout;
        timeout.tv_sec = 1;  
        timeout.tv_usec = 0;

        if (select(idSocket + 1, &readfds, nullptr, nullptr, &timeout) > 0) 
        {
            addr_len = sizeof(adr_client);
            SOCKET clientSocket = accept(idSocket, (struct sockaddr*)&adr_client, &addr_len);
          
            if (clientSocket != INVALID_SOCKET) 
            {
                idsClients.push_back(clientSocket);
                handleClient(clientSocket);
                waitClientInstruction(clientSocket);
            }
        }
    }
}

void TCPServer::closeClientSocket(SOCKET clientSocket)
{
    closesocket(clientSocket);
}

void TCPServer::waitClientInstruction(SOCKET clientId)
{
    while (isServerOn)
    {
        receiveMessageFromClient(clientId);

        //Then according behavior tree / state machine
        sendMessage("Reponse");
    }
}

std::string TCPServer::receiveMessageFromClient(SOCKET clientId)
{
    uint trameLenght = recv(clientId, trame_lect, DIMMAX, 0);
    trame_lect[trameLenght] = '\0';
    return trame_lect;
}

void TCPServer::closeSocket()
{
    isServerOn = false;
    listenerThread.join();
    closesocket(idSocket);
}

void TCPServer::handleClient(SOCKET clientSocket)
{
   
}

