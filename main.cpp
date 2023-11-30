//Fichier du main, (main.cpp)

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Boat.h"
#include "Grid.h"
#include "Settings.h"
#include "AnimatedBackground.h"

/*----Settings-----*/
const int fps = 15;
const sf::Color bgColor = sf::Color::Black;
sf::Vector2f windowSize(1600, 850);


int main() {
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "BattleShip");

    GridSettings gridSettings;

    std::vector<Entity*> entitiesPtr;

    Boat* selectedBoat = nullptr;

    AnimatedBackground gameBackground("ressources/UI/backgrounds/waterBg/Layer ", 59, 100, true, windowSize);
    //entitiesPtr.push_back(&gameBackground);

    Grid gridPlayer(gridSettings.nbPixels, gridSettings.squareSize, gridSettings.playerGridPosition, gridSettings.lineColor);
    Grid gridEnemy(gridSettings.nbPixels, gridSettings.squareSize, gridSettings.ennemyGridPosition, gridSettings.lineColor);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        gameBackground.draw(window);

        gridPlayer.DrawGrid(window);
        gridEnemy.DrawGrid(window);

        //Polymorphisme Wesh :p
        for (int i = 0; i < entitiesPtr.size(); i++)
        {
            entitiesPtr.at(i)->draw(window);
        }

        window.display();
        window.clear(bgColor);
    }

    return 0;
}




