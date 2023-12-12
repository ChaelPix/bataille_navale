#include <SFML/Graphics.hpp>
#include <iostream>


#include "BattleshipServer.h"

void ServerMod()
{
    ushort port = 12345;

    BattleshipServer server(port);
    std::cout << "Serveur d\202marr\202 sur le port " << port << ". Entrez le mdp 1234 pour arr�ter..." << std::endl;

    std::string s  = "";

    while (s != "1234")
        std::cin >> s;

    server.closeSocket();
}

int main() {
    ServerMod();
    return 0;
}


