//Fichier du main, (main.cpp)

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Localization.h"
#include "CoreGame.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1300, 850), "BattleShip");

    // Création de l'instance de CoreGame
    CoreGame coreGame;

    // Initialisation des textures et des sprites des bateaux
    std::vector<sf::Texture> shipTextures; // Textures pour les différents types de bateaux
    std::vector<sf::Sprite> shipSprites;   // Sprites pour les bateaux

    sf::Texture shipTexture;
    if (!shipTexture.loadFromFile("ressources/UI/ui_boat_prototype.png")) {
        std::cerr << "Erreur de chargement de la texture du bateau" << std::endl;
        return 1;
    }

    // Charger les textures et initialiser les sprites
    // Exemple pour un seul type de bateau
    sf::Texture texture2; // bateaux 2 cases
    if (texture2.loadFromFile("ressources/UI/ui_boat_prototype.png")) {
        shipTextures.push_back(texture2);
        sf::Sprite sprite;
        sprite.setTexture(texture2);
        // Définir la position initiale, la taille, etc.
        shipSprites.push_back(sprite);
    }

    // Charger les textures et initialiser les sprites
// Exemple pour un seul type de bateau
    sf::Texture texture3; // bateaux 3 cases
    if (texture3.loadFromFile("ressources/UI/ui_boat_prototype.png")) {
        shipTextures.push_back(texture3);
        sf::Sprite sprite3;
        sprite3.setTexture(texture3);
        // Définir la position initiale, la taille, etc.
        shipSprites.push_back(sprite3);
    }

    // Charger les textures et initialiser les sprites
// Exemple pour un seul type de bateau
    sf::Texture texture4; // bateaux 4 cases
    if (texture4.loadFromFile("ressources/UI/ui_boat_prototype.png")) {
        shipTextures.push_back(texture4);
        sf::Sprite sprite4;
        sprite4.setTexture(texture4);
        // Définir la position initiale, la taille, etc.
        shipSprites.push_back(sprite4);
    }

    // Charger les textures et initialiser les sprites
// Exemple pour un seul type de bateau
    sf::Texture texture5; // bateaux 5 cases
    if (texture5.loadFromFile("ressources/UI/ui_boat_prototype.png")) {
        shipTextures.push_back(texture5);
        sf::Sprite sprite5;
        sprite5.setTexture(texture5);
        // Définir la position initiale, la taille, etc.
        shipSprites.push_back(sprite5);
    }

    sf::Sprite shipSprite;
    shipSprite.setTexture(shipTexture);
    shipSprite.setPosition(100, 100); // Position initiale
    shipSprite.setScale(0.3854, 0.55); 

    bool dragging = false;
    sf::Sprite* selectedShip = nullptr;


    const int gridSize = 50; // Taille d'une cellule de la grille (en pixels)
    const sf::Vector2i gridOrigin(100, 100); // Origine de la grille
    const int gridRows = 10;
    const int gridCols = 10;

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
                        int mouseX = std::min(std::max(event.mouseButton.x, gridOrigin.x), gridOrigin.x + gridCols * gridSize);
                        int mouseY = std::min(std::max(event.mouseButton.y, gridOrigin.y), gridOrigin.y + gridRows * gridSize);

                        int gridX = (mouseX - gridOrigin.x) / gridSize;
                        int gridY = (mouseY - gridOrigin.y) / gridSize;

                        sf::Vector2f newPosition(gridOrigin.x + gridX * gridSize, gridOrigin.y + gridY * gridSize);
                        selectedShip->setPosition(newPosition);

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

        sf::Color couleurAvecOpacite(255, 255, 255, 100); // Rouge avec une opacité de 128
        // Dessiner la grille
        sf::RectangleShape line(sf::Vector2f(500, 1));
        line.setFillColor(couleurAvecOpacite);

        for (int i = 0; i <= 10; ++i) {
            line.setPosition(100, i * 50 + 100);
            window.draw(line);
            line.setSize(sf::Vector2f(1, 500));
            line.setPosition(i * 50 + 100, 100);
            window.draw(line);
            line.setSize(sf::Vector2f(500, 1)); // Réinitialiser pour les lignes horizontales
        }
        for (auto& sprite : shipSprites) {
            window.draw(sprite);
        }
        // Dessiner le bateau
        window.draw(shipSprite);
        window.display();
        window.clear();
    }

    return 0;
}











////Fichier du main, (main.cpp)
//
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include "Localization.h"
//#include "CoreGame.h"
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(1300, 850), "BattleShip");
//
//    sf::Texture shipTexture;
//    if (!shipTexture.loadFromFile("ressources/UI/ui_boat_prototype.png")) {
//        std::cerr << "Erreur de chargement de la texture du bateau" << std::endl;
//        return 1;
//    }
//
//    sf::Sprite shipSprite;
//    shipSprite.setTexture(shipTexture);
//    shipSprite.setPosition(100, 100); // Position initiale
//    shipSprite.setScale(0.3854, 0.55);
//
//    bool dragging = false;
//    sf::Sprite* selectedShip = nullptr;
//
//
//    const int gridSize = 50; // Taille d'une cellule de la grille (en pixels)
//    const sf::Vector2i gridOrigin(100, 100); // Origine de la grille
//    const int gridRows = 10;
//    const int gridCols = 10;
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//
//            // Gestion des événements de la souris
//            if (event.type == sf::Event::MouseButtonPressed) {
//                if (event.mouseButton.button == sf::Mouse::Left) {
//                    if (shipSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//                        dragging = true;
//                        selectedShip = &shipSprite;
//                    }
//                }
//            }
//
//            if (event.type == sf::Event::MouseButtonReleased) {
//                if (event.mouseButton.button == sf::Mouse::Left) {
//                    dragging = false;
//
//                    if (selectedShip != nullptr) {
//                        int mouseX = std::min(std::max(event.mouseButton.x, gridOrigin.x), gridOrigin.x + gridCols * gridSize);
//                        int mouseY = std::min(std::max(event.mouseButton.y, gridOrigin.y), gridOrigin.y + gridRows * gridSize);
//
//                        int gridX = (mouseX - gridOrigin.x) / gridSize;
//                        int gridY = (mouseY - gridOrigin.y) / gridSize;
//
//                        sf::Vector2f newPosition(gridOrigin.x + gridX * gridSize, gridOrigin.y + gridY * gridSize);
//                        selectedShip->setPosition(newPosition);
//
//                        selectedShip = nullptr;
//                    }
//
//                    // Autres logiques potentielles
//                    // ...
//                }
//            }
//
//
//            if (event.type == sf::Event::MouseMoved) {
//                if (dragging && selectedShip != nullptr) {
//                    selectedShip->setPosition(event.mouseMove.x, event.mouseMove.y);
//                }
//            }
//        }
//
//        sf::Color couleurAvecOpacite(255, 255, 255, 100); // Rouge avec une opacité de 128
//        // Dessiner la grille
//        sf::RectangleShape line(sf::Vector2f(500, 1));
//        line.setFillColor(couleurAvecOpacite);
//
//        for (int i = 0; i <= 10; ++i) {
//            line.setPosition(100, i * 50 + 100);
//            window.draw(line);
//            line.setSize(sf::Vector2f(1, 500));
//            line.setPosition(i * 50 + 100, 100);
//            window.draw(line);
//            line.setSize(sf::Vector2f(500, 1)); // Réinitialiser pour les lignes horizontales
//        }
//        // Dessiner le bateau
//        window.draw(shipSprite);
//        window.display();
//        window.clear();
//    }
//
//    return 0;
//}
