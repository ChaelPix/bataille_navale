#include <SFML/Graphics.hpp>
#include <iostream>

#include "Application.h"
#include "BattleshipServer.h"

void ServerMod()
{
    ushort port = 12345;

    BattleshipServer server(port);
    std::cout << "Serveur d\202marr\202 sur le port " << port << ". Appuyez sur Entr\202e pour arrêter..." << std::endl;

    std::cin.get();
    server.closeSocket();
}

void launchMenu()
{
    GameApplication game;
    game.Run();
}

void launchGame()
{
    GameApplication game(GameApplication::State::Game);
    game.Run();
}

int main() {

    std::cout << "[DEBUG] SELECT MENU: " << std::endl
        << "[0] Main Menu " << std::endl
        << "[1] Game Menu " << std::endl
        << "[2] Server Mod " << std::endl;

    char x;
    std::cin >> x;

    switch (x)
    {
        case '1':    
            launchGame();
            break;

        case '2':
            ServerMod();
            break;

        default:
            launchMenu();
            break;
    }


    return 0;
}


