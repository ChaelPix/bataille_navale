//Fichier du main, (main.cpp)

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Localization.h"
#include "CoreGame.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1300, 850), "BattleShip");

    sf::Texture shipTexture;
    if (!shipTexture.loadFromFile("ressources/UI/ui_boat_prototype.png")) {
        std::cerr << "Erreur de chargement de la texture du bateau" << std::endl;
        return 1;
    }

    sf::Sprite shipSprite;
    shipSprite.setTexture(shipTexture);
    shipSprite.setPosition(100, 100); // Position initiale
    shipSprite.setScale(0.3854, 0.55); //

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
                    if (shipSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        dragging = true;
                        selectedShip = &shipSprite;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    dragging = false;

                    if (selectedShip != nullptr) {
                        // Calculer la position de la grille la plus proche
                        int gridSize = 50; // Taille d'une cellule de la grille (en pixels)
                        int mouseX = event.mouseButton.x;
                        int mouseY = event.mouseButton.y;

                        // Trouver l'indice de la grille le plus proche
                        int gridX = mouseX / gridSize;
                        int gridY = mouseY / gridSize;

                        // Calculer la nouvelle position du sprite en fonction de la grille
                        sf::Vector2f newPosition(gridX * gridSize, gridY * gridSize);

                        // Mettre à jour la position du bateau
                        selectedShip->setPosition(newPosition);

                        // Réinitialiser le bateau sélectionné
                        selectedShip = nullptr;
                    }

                    // Autres logiques potentielles
                    // ...
                }
            }


            if (event.type == sf::Event::MouseMoved) {
                if (dragging && selectedShip != nullptr) {
                    selectedShip->setPosition(event.mouseMove.x, event.mouseMove.y);
                }
            }
        }

      

        // Dessiner la grille
        sf::RectangleShape line(sf::Vector2f(800, 1));
        line.setFillColor(sf::Color::White);
        for (int i = 0; i <= 10; ++i) {
            line.setPosition(100, i * 50 + 100);
            window.draw(line);
            line.setSize(sf::Vector2f(1, 500));
            line.setPosition(i * 50 + 100, 100);
            window.draw(line);
            line.setSize(sf::Vector2f(800, 1)); // Réinitialiser pour les lignes horizontales
        }
        // Dessiner le bateau
        window.draw(shipSprite);
        window.display();
        window.clear();
    }

    return 0;
}
