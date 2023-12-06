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

void launchSplash()
{
    GameApplication game(GameApplication::State::Splash);
    game.Run();
}

void launchMenu()
{
    GameApplication game(GameApplication::State::Menu);
    game.Run();
}

void launchGame()
{
    GameApplication game(GameApplication::State::Game);
    game.Run();
}


int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::cout << "[DEBUG] SELECT MENU: " << std::endl
        << "[1] Splash Menu " << std::endl
        << "[2] Main Menu " << std::endl
        << "[3] Game menu " << std::endl
        << "[4] Server Mod " << std::endl;

    char x;
    std::cin >> x;
    system("cls");

    switch (x)
    {
        case '1':
            launchSplash();
            break;

        case '3':    
            launchGame();
            break;

        case '4':
            ServerMod();
            break;

        default:
            launchMenu();
            break;
    }


    return 0;
}


