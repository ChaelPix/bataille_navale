//Fichier du main, (main.cpp)

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Boat.h"
#include "Grid.h"
#include "Settings.h"

/*----Settings-----*/
const int fps = 15;
const sf::Color bgColor = sf::Color::Black;

int main() {
    sf::RenderWindow window(sf::VideoMode(1300, 850), "BattleShip");

    GridSettings gridSettings;

    Boat* selectedBoat = nullptr;

    Grid gridPlayer(gridSettings.nbPixels, gridSettings.squareSize, gridSettings.playerGridPosition, gridSettings.lineColor);
    Grid gridEnemy(gridSettings.nbPixels, gridSettings.squareSize, gridSettings.ennemyGridPosition, gridSettings.lineColor);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        gridPlayer.DrawGrid(window);
        gridEnemy.DrawGrid(window);

        window.display();
        window.clear(bgColor);
    }

    return 0;
}




