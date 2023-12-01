//Fichier du main, (main.cpp)

#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerBoatsManager.h"
#include "Grid.h"
#include "Settings.h"
#include "AnimatedBackground.h"
#include "MouseManager.h"

/*----Settings-----*/
const int fps = 15;
const sf::Color bgColor = sf::Color::Black;
sf::Vector2f windowSize(1600, 850);


int main() {

    /***************___WINDOW___***************/
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "BattleShip");
    MouseManager mouseManager;

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
    PlayerBoatsManager playerBoatsManager;
    
    /***************___GAME WINDOW___***************/
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

           
        }
        mouseManager.update(event, window);

        /*___BG___*/
        gameBackground.draw(window);

        /*___Grids___*/
        gridPlayer.DrawGrid(window);
        gridEnemy.DrawGrid(window);

        /*___Boats___*/
        playerBoatsManager.dragBoats(mouseManager);
        playerBoatsManager.draw(window);

        /*___Entities (Polymorphism :p)___*/
        for (int i = 0; i < entitiesPtr.size(); i++)
            entitiesPtr.at(i)->draw(window);
        

        /*___GameWindow Reset___*/
        window.display();
        window.clear(bgColor);
    }

    return 0;
}


//
//
//if (dragging && selectedBoat != nullptr) {
//    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
//    int gridX = (worldPos.x - gridOrigin.x) / gridSize;
//    int gridY = (worldPos.y - gridOrigin.y) / gridSize;
//    gridX = std::max(0, std::min(gridX, gridCols - 1));
//    gridY = std::max(0, std::min(gridY, gridRows - 1));
//
//    sf::Vector2f snappedPosition(gridOrigin.x + gridX * gridSize, gridOrigin.y + gridY * gridSize);
//    selectedBoat->setPosition(snappedPosition);
//
//    std::cout << "Bateau choisi : " << selectedBoat->getBoatId()
//        << "\t taille : " << static_cast<int>(selectedBoat->getBoatType())
//        << "\t nb colonne : " << gridX
//        << "\t nb ligne : " << gridY
//        << std::endl;
//}