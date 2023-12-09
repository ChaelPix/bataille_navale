#include "TCPClient.h"

TCPClient::TCPClient(const std::string& serverIP, ushort serverPORT) : TCPWinsocksMaster(serverPORT), serverIP(serverIP)
{
	init();
}

void TCPClient::init()
{
	connectToServer();
    startReceiving();
}

void TCPClient::connectToServer()
{
    adr_server.sin_family = AF_INET;
    adr_server.sin_port = htons(serverPORT);

    //std::cout << "\nClient :" << idSocket;
    inet_pton(AF_INET, serverIP.c_str(), &adr_server.sin_addr);
    if (connect(idSocket, (struct sockaddr*)&adr_server, sizeof(adr_server)) < 0) {
        throw std::runtime_error("Connect to Server Failed");
    }
}

void TCPClient::startReceiving() {
    receiveThread = std::thread(&TCPClient::receiveMessages, this);
}

void TCPClient::receiveMessages() {
    while (receiving) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(idSocket, &readfds);

        struct timeval timeout;
        timeout.tv_sec = 1;

        int result = select(idSocket + 1, &readfds, NULL, NULL, &timeout);

        if (result == 0) {
            continue;
        }
        else if (result == -1) {
            break;
        }
        else {
            std::string message = receiveMessage();
            std::lock_guard<std::mutex> lock(queueMutex);
            messageQueue.push(message);
            cv.notify_one();
        }
    }
}

std::string TCPClient::getMessage() {
    std::lock_guard<std::mutex> lock(queueMutex);
    if (!messageQueue.empty()) {
        std::string message = messageQueue.front();
        messageQueue.pop();
        
        return message;
    }
    return "";
}


void TCPClient::stopReceiving() {
    std::cout << "stopReceiving" << std::endl;
    receiving = false;
    if (receiveThread.joinable()) {
        receiveThread.join();
    }
}

TCPClient::~TCPClient() {
    std::cout << "Dans Destructeur" << std::endl;
    stopReceiving();
    std::cout << "DClose Destructeyr" << std::endl;
    closeSocket();
}

