#include <SFML/Graphics.hpp>
#include <iostream>
#include "TCPClient.h"
#include "TCPServer.h"

#include <Windows.h>
int main() {
    try {
        ushort port = 12345;
        TCPServer server(port);

        std::cout << "Serveur d\202marr\202 sur le port " << port << ". Appuyez sur Entr\202e pour arrêter..." << std::endl;
        
        Sleep(1000);
        std::cout << "Cr\202ation Client 1 & 2" << std::endl;

        TCPClient tcpClient1("10.187.52.31", 12345);
        TCPClient tcpClient2("10.187.52.31", 12345);
        Sleep(1000);
        std::cout << tcpClient1.receiveMessage() << std::endl;
        std::cout << tcpClient2.receiveMessage() << std::endl;
        Sleep(1000);
        tcpClient1.sendMessage("bonjour 1");
        tcpClient2.sendMessage("ok");
        Sleep(1000);
        std::cout << tcpClient1.receiveMessage() << std::endl;
        std::cout << tcpClient2.receiveMessage() << std::endl;
        Sleep(1000);
        tcpClient1.closeSocket();
        tcpClient2.closeSocket();

        server.closeSocket();
        std::cout << "Serveur arret\202." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}