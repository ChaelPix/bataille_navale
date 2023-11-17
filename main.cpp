#include <SFML/Graphics.hpp>
#include <iostream>
#include "Localization.h"
#include "CoreGame.h"

int main()
{

    sf::RenderWindow window(sf::VideoMode(600, 800), "BattleShip");

    sf::Texture shipTexture;
    if (!shipTexture.loadFromFile("ressources/UI/ui_boat_prototype.png")) {
        // erreur de chargement
    }

    sf::Sprite shipSprite;
    shipSprite.setTexture(shipTexture);
    shipSprite.setPosition(100, 100); // position initiale

    // Dans la boucle de jeu
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Gérer d'autres événements, comme les mouvements de la souris
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Mettre à jour la position du sprite de bateau, etc.
                }
            }
        }

        window.clear();
        window.draw(shipSprite); // dessiner le sprite
        window.display();
    }


    return 0;
}