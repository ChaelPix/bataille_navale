//Fichier du main, (main.cpp)

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Application.h"

/*----Settings-----*/
const int fps = 15;


int main() {

    GameApplication game(GameApplication::State::Game);
    game.Run();

    return 0;
}


