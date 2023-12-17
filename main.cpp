#include <SFML/Graphics.hpp>
#include <iostream>


#include "BattleshipServer.h"

void ServerMod()
{
    ushort port = 12345;

    BattleshipServer server(port);
    std::cout << "Serveur d\202marr\202 sur le port " << port << ". Entrez 'STOP' pour arrêter..." << std::endl;

    std::string s  = "";

    while (s != "STOP")
        std::cin >> s;

    server.closeSocket();
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    ServerMod();
    return 0;
}


