#include <SFML/Graphics.hpp>
#include <iostream>
#include "Localization.h"
#include "CoreGame.h"

int main()
{

    sf::RenderWindow window(sf::VideoMode(1300, 850), "BattleShip");

    sf::Texture shipTexture;
    if (!shipTexture.loadFromFile("ressources/UI/ui_boat_prototype.png")) {
        // erreur de chargement
    }

    sf::Sprite shipSprite;
    shipSprite.setTexture(shipTexture);
    shipSprite.setPosition(100, 100); // position initiale

    bool dragging = false;
    sf::Sprite* selectedShip = nullptr;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Gestion des événements de la souris
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Vérifier si on clique sur un bateau
                    if (shipSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        dragging = true;
                        selectedShip = &shipSprite;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    dragging = false;
                    selectedShip = nullptr;
                    // Vérifiez si le bateau est dans une position valide et mettez à jour la grille
                    // ...
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                if (dragging && selectedShip != nullptr) {
                    // Mettre à jour la position du bateau avec la souris
                    selectedShip->setPosition(event.mouseMove.x, event.mouseMove.y);
                }
            }
        }

        window.clear();
        window.draw(shipSprite);
        window.display();
    }



    return 0;
}