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
    Boat boat2(1, CoreGame::typeBateau::Torpilleur, sf::Vector2f(gridSize * (int)CoreGame::typeBateau::Torpilleur, gridSize));
    boat1.setPosition(500, 100);
    boat2.setPosition(500, 300);

    bool dragging = false;
    Boat* selectedBoat = nullptr;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (boat1.getShape().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    dragging = true;
                    selectedBoat = &boat1;
                }
                else if (boat2.getShape().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    dragging = true;
                    selectedBoat = &boat2;
                }
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                dragging = false;
                selectedBoat = nullptr;
                
                // Autres logiques potentielles
                // ...
            }
        }

        if (dragging && selectedBoat != nullptr) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
            int gridX = (worldPos.x - gridOrigin.x) / gridSize;
            int gridY = (worldPos.y - gridOrigin.y) / gridSize;
            gridX = std::max(0, std::min(gridX, gridCols - 1));
            gridY = std::max(0, std::min(gridY, gridRows - 1));

            sf::Vector2f snappedPosition(gridOrigin.x + gridX * gridSize, gridOrigin.y + gridY * gridSize);
            selectedBoat->setPosition(snappedPosition);

            std::cout << "Bateau choisi : " << selectedBoat->getBoatId()
                << "\t taille : " << static_cast<int>(selectedBoat->getBoatType())
                << "\t nb colonne : " << gridX
                << "\t nb ligne : " << gridY
                << std::endl;
        }

        // Dessiner la grille
        sf::RectangleShape line(sf::Vector2f(500, 1));
        line.setFillColor(sf::Color::Blue);
        for (int i = 0; i <= 10; ++i) {
            line.setPosition(100, i * 50 + 100);
            window.draw(line);
            line.setSize(sf::Vector2f(1, 500));
            line.setPosition(i * 50 + 100, 100);
            window.draw(line);
            line.setSize(sf::Vector2f(500, 1)); 
        }

        boat1.draw(window);
        boat2.draw(window);


        window.display();
        window.clear();
    }

    return 0;
}




