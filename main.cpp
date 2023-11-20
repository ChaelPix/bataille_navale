//Fichier du main, (main.cpp)

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Boat.h"
#include "CoreGame.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1300, 850), "BattleShip");

    const int gridSize = 50; // Taille d'une cellule de la grille (en pixels)
    const sf::Vector2i gridOrigin(100, 100); // Origine de la grille
    const int gridRows = 10;
    const int gridCols = 10;

    /*A mettre les textures dans une classe texture manager*/
    sf::Texture texture;

    Boat boat1(0, CoreGame::typeBateau::PorteAvion, sf::Vector2f(gridSize * (int)CoreGame::typeBateau::PorteAvion, gridSize));


    bool dragging = false;
    Entity* selectedShip = nullptr;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        boat1.draw(window);


        window.display();
        window.clear();
    }

    return 0;
}




