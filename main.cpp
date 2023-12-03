#include <SFML/Graphics.hpp>
#include <iostream>

#include "Application.h"

int main() {

    std::cout << "[DEBUG] SELECT MENU: " << std::endl
        << "[0] Main Menu " << std::endl
        << "[1] Game Menu " << std::endl;

    char x;
    std::cin >> x;

    if (x != '0')
    {
        GameApplication game(GameApplication::State::Game);
        game.Run();
    }
    else {
        GameApplication game;
        game.Run();
    }

    return 0;
}


