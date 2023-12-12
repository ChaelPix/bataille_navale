#include <SFML/Graphics.hpp>
#include <iostream>
#include "Application.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    GameApplication game(GameApplication::State::Splash);
    game.Run();

    return 0;
}

