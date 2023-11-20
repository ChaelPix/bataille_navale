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
        std::cin.get();

        server.closeSocket();
        std::cout << "Serveur arret\202." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}