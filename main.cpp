#include <SFML/Graphics.hpp>
#include <iostream>

#include "Application.h"

int main() {

    GameApplication game(GameApplication::State::Game);
    game.Run();

    return 0;
}


