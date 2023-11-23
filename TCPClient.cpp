#include "TCPClient.h"
#pragma comment(lib, "ws2_32.lib") // Lien vers la bibliothèque Winsock

TCPClient::TCPClient() : isConnected(false) {
    WSAStartup(MAKEWORD(2, 0), &WSAData);
}

TCPClient::~TCPClient() {
    if (isConnected) {
        closesocket(serverSocket);
    }
    WSACleanup();
}

bool TCPClient::connectToServer(const std::string& address, int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_addr.s_addr = inet_addr(address.c_str());
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (connect(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) != 0) {
        std::cerr << "Connexion au serveur échouée." << std::endl;
        return false;
    }

    std::cout << "Connecté au serveur!" << std::endl;
    isConnected = true;
    return true;
}

bool TCPClient::sendMessage(const std::string& message) {
    if (send(serverSocket, message.c_str(), message.size(), 0) < 0) {
        std::cerr << "Échec de l'envoi du message." << std::endl;
        return false;
    }
    return true;
}

std::string TCPClient::receiveMessage() {
    char buffer[1024] = { 0 };
    int bytesReceived = recv(serverSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived < 0) {
        std::cerr << "Erreur de réception du message." << std::endl;
        return "";
    }
    return std::string(buffer, bytesReceived);
}

void TCPClient::closeConnection() {
    if (isConnected) {
        closesocket(serverSocket);
        isConnected = false;
        std::cout << "Connexion fermée." << std::endl;
    }
}
