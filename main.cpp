#include <SFML/Graphics.hpp>
#include <iostream>


#include "Application.h"
#include "BattleshipServer.h"

void ServerMod()
{
    ushort port = 12345;

    BattleshipServer server(port);
    std::cout << "Serveur d\202marr\202 sur le port " << port << ". Entrez le mdp 1234 pour arrêter..." << std::endl;

    std::string s  = "";

    while (s != "1234")
        std::cin >> s;

    server.closeSocket();
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    GameApplication game(GameApplication::State::Splash);
    game.Run();

    return 0;
}


