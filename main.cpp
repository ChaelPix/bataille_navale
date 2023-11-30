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

    /***************___WINDOW___***************/
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "BattleShip");

    /***************___BACKGROUND___***************/
    AnimatedBackground gameBackground("ressources/UI/backgrounds/waterBg/Layer ", 59, 100, true, windowSize);
    //entitiesPtr.push_back(&gameBackground);

     /***************___GRID___***************/
    GridSettings gridSettings;
    Grid gridPlayer(gridSettings.nbPixels, gridSettings.squareSize, gridSettings.playerGridPosition, gridSettings.lineColor);
    Grid gridEnemy(gridSettings.nbPixels, gridSettings.squareSize, gridSettings.ennemyGridPosition, gridSettings.lineColor);

    /***************___ENTITIES___***************/
    std::vector<Entity*> entitiesPtr;

    /***************___BOATS___***************/
    Boat* selectedBoat = nullptr;



    /***************___GAME WINDOW___***************/
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /*___BG___*/
        gameBackground.draw(window);

        /*___Grids___*/
        gridPlayer.DrawGrid(window);
        gridEnemy.DrawGrid(window);

        /*___Entities (Polymorphism :p)___*/
        for (int i = 0; i < entitiesPtr.size(); i++)
            entitiesPtr.at(i)->draw(window);
        

        /*___GameWindow Reset___*/
        window.display();
        window.clear(bgColor);
    }

    return 0;
}




