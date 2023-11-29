////fichier du main en sfml
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include "Boat.h"
//#include "CoreGame.h"
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(1300, 850), "BattleShip");
//
//    const int gridSize = 50; // Taille d'une cellule de la grille (en pixels)
//    const sf::Vector2i gridOrigin(100, 100); // Origine de la grille
//    const int gridRows = CoreGame::nbLig;
//    const int gridCols = CoreGame::nbCol;
//
//    // Ajoutez ici vos textures, bateaux, etc.
//    Boat boat1(1, CoreGame::typeBateau::PorteAvion, sf::Vector2f(gridSize * (int)CoreGame::typeBateau::PorteAvion, gridSize));
//    Boat boat2(2, CoreGame::typeBateau::Croiseur, sf::Vector2f(gridSize * (int)CoreGame::typeBateau::Croiseur, gridSize));
//    Boat boat3(3, CoreGame::typeBateau::ContreTorpilleur, sf::Vector2f(gridSize * (int)CoreGame::typeBateau::ContreTorpilleur, gridSize));
//    Boat boat4(4, CoreGame::typeBateau::Torpilleur, sf::Vector2f(gridSize * (int)CoreGame::typeBateau::Torpilleur, gridSize));
//
//    bool dragging = false;
//    Boat* selectedBoat = nullptr;
//    CoreGame coreGame; // Instance de votre jeu
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//
//            if (event.type == sf::Event::MouseButtonPressed) {
//                if (event.mouseButton.button == sf::Mouse::Left) {
//                    // Vérifiez si le clic est sur un bateau
//                    if (boat1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
//                        dragging = true;
//                        selectedBoat = &boat1;
//                    }
//                    // Répétez pour les autres bateaux
//                }
//            }
//            if (event.type == sf::Event::MouseButtonReleased) {
//                if (event.mouseButton.button == sf::Mouse::Left && selectedBoat != nullptr) {
//                    dragging = false;
//                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//                    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
//                    int gridX = (worldPos.x - gridOrigin.x) / gridSize;
//                    int gridY = (worldPos.y - gridOrigin.y) / gridSize;
//
//                    if (coreGame.estPlacementValide(boat1.getBoatType(), gridX, gridY, boat1.getDirection())) {
//                        coreGame.placerBateau(boat1.getBoatType(), gridX, gridY, boat1.getDirection());
//                        // Autres actions, comme mettre à jour la position du bateau dans l'interface
//                    }
//
//                    else {
//                        // Informez l'utilisateur que le placement est invalide
//                    }
//                    selectedBoat = nullptr;
//                }
//            }
//
//            if (dragging && selectedBoat != nullptr) {
//                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//                selectedBoat->setPosition(mousePos - sf::Vector2f(selectedBoat->getSize().x / 2, selectedBoat->getSize().y / 2));
//            }
//        }
//
//        window.clear();
//        // Dessiner la grille
//        for (int i = 0; i <= gridRows; ++i) {
//            sf::RectangleShape line(sf::Vector2f(gridSize * gridCols, 1));
//            line.setPosition(gridOrigin.x, gridOrigin.y + i * gridSize);
//            window.draw(line);
//        }
//        for (int i = 0; i <= gridCols; ++i) {
//            sf::RectangleShape line(sf::Vector2f(1, gridSize * gridRows));
//            line.setPosition(gridOrigin.x + i * gridSize, gridOrigin.y);
//            window.draw(line);
//        }
//        // Dessiner les bateaux ici
//        boat1.draw(window);
//        boat2.draw(window);
//        boat3.draw(window);
//        boat4.draw(window);
//
//        // Dessinez la grille, les bateaux, et d'autres éléments de l'interface
//        window.display();
//    }
//
//    return 0;
//}





#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <iomanip> // Pour std::setw et std::setfill
#include <sstream> // Pour std::stringstream
#include <algorithm>    // std::max

std::string getFileName(int number) {
    std::stringstream ss;
    ss << "BackGroundDoc/background" << std::setw(5) << std::setfill('0') << number << ".jpg";
    return ss.str();
}

struct ShopItem {
    sf::Sprite sprite;
    sf::Text title;
    float originalY; // Position Y originale pour le sprite
    float originalTitleY; // Position Y originale pour le titre

    ShopItem(const sf::Texture& texture, const sf::Font& font, const std::string& titleStr, float posY, float titlePosY)
        : originalY(posY), originalTitleY(titlePosY) {
        sprite.setTexture(texture);
        title.setFont(font);
        title.setString(titleStr);
        title.setCharacterSize(24); // Taille du texte
        title.setFillColor(sf::Color::White);

        sprite.setPosition(0, posY);
        title.setPosition(0, titlePosY);
    }
};


std::vector<sf::Texture> loadTextures(int numberOfItems, const std::string& basePath) {
    std::vector<sf::Texture> textures;
   
    return textures;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1333, 749), "Menu d'accueil");
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/laurentr/Pictures/background.jpg")) {
        return -1;
    }
    sf::Sprite backgrounds(backgroundTexture);
    sf::Font font;
    if (!font.loadFromFile("Fonts/AGENCYB.ttf")) {
        return -1;
    }

    sf::Text playButton("JOUER", font, 90);
    playButton.setPosition(1280 - playButton.getGlobalBounds().width, 312);

    sf::Text settingsButton("SETTINGS", font, 40);
    settingsButton.setPosition(1262 - settingsButton.getGlobalBounds().width, 200);

    sf::Text shop("ITEM-SHOP", font, 40);
    shop.setPosition(1272 - shop.getGlobalBounds().width, 488);


    bool isMenuScreen = true; // pour gérer l'affichage du menu
    bool isSettingsScreen = true; // pour gérer l'affichage des parametres
    bool isShopScreen = true; // pour gérer l'affichage de la boutique

    ////////////////////---background---//////////////////////

    int X = 146; // Nombre total d'images
    std::vector<sf::Texture> textures(X);

    // Chargement des textures
    for (int i = 0; i < X; ++i) {
        std::string fileName = getFileName(i * 2 + 1); // Générer le nom de fichier
        if (!textures[i].loadFromFile(fileName)) {
            std::cerr << "Erreur de chargement pour l'image " << fileName << std::endl;
            return -1;
        }
    }

    sf::Sprite background;
    sf::Clock clock;
    bool ascending = true;
    int index = 0;


    sf::Text Casier("Casier", font, 30);
    Casier.setPosition(100, 200);
    sf::Text retour("retour", font, 30);
    retour.setPosition(100, 300);

    ////////////////////---Boutique---//////////////////////

    // Définissez ces variables en haut de votre fonction main ou en tant que constantes globales
    const float itemWidth = 200.0f; // Largeur d'un élément de la boutique
    const float itemHeight = 200.0f; // Hauteur d'un élément de la boutique
    const float spacing = 20.0f; // Espacement entre les éléments de la boutique


    // Supposons que vous ayez chargé des textures dans un vecteur de sf::Texture
    std::vector<sf::Texture> texturesShop;
    int numberOfItems = 49; // Remplacez par le nombre réel d'éléments dans votre boutique

    std::string basePath = "ressources/profilPictures/caractere"; // Chemin de base pour les images

    for (int i = 0; i < numberOfItems; ++i) {
        sf::Texture ShopSFMLtexture;

        // Essayez avec le format PNG
        if (!ShopSFMLtexture.loadFromFile(basePath + std::to_string(i + 1) + ".png")) {
           
        }
        else {
            texturesShop.push_back(ShopSFMLtexture);
        }
    }


    // Création des ShopItem avec texturesShop
    std::vector<ShopItem> items;
    int itemsPerRow = 4; // Nombre d'items par ligne
    int currentRow = 0;
    int currentColumn = 0;

    for (int i = 0; i < texturesShop.size(); ++i) {
        float posX = 10 + currentColumn * (itemWidth + spacing);
        float posY = 100 + currentRow * (itemHeight + spacing);

        items.emplace_back(texturesShop[i], font, "Item " + std::to_string(i + 1), posY, posY + itemHeight);

        currentColumn++;
        if (currentColumn >= itemsPerRow) {
            currentColumn = 0;
            currentRow++;
        }

        // Redimensionnement
        float targetWidth = 200.0f; // Largeur cible
        float targetHeight = 200.0f; // Hauteur cible
        float scaleX = targetWidth / items[i].sprite.getGlobalBounds().width;
        float scaleY = targetHeight / items[i].sprite.getGlobalBounds().height;
        items[i].sprite.setScale(scaleX, scaleY);
    }

    // Disposition des items (à ajuster selon vos besoins)
    for (int i = 0; i < items.size(); ++i) {
        items[i].sprite.setPosition(10 + i * 100, 100); // Positionnez les sprites
        items[i].title.setPosition(10 + i * 100, 200); // Positionnez les titres
    }


    float scrollOffset = 0.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Détection de clic sur le bouton Jouer
                    if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isMenuScreen = false; // change l'écran
                        isSettingsScreen = false;
                        // Logique pour le nouvel écran de jeu
                    }

                    // Détection de clic sur le bouton Paramètres
                    if (settingsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isMenuScreen = false; // change l'écran
                        isSettingsScreen = true;
                        // Logique pour l'écran des paramètres
                    }

                    // Détection de clic sur le bouton ITEM-SHOP
                    if (shop.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isMenuScreen = false;
                        isSettingsScreen = false;
                        isShopScreen = true; // Active l'écran de la boutique
                    }

                    // Détection de clic sur le bouton Jouer
                    if (retour.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isMenuScreen = true; // change l'écran
                        isSettingsScreen = false;
                        // Logique pour le nouvel écran de jeu
                    }
                    // Gestion du défilement
                    if (event.type == sf::Event::MouseWheelScrolled && isShopScreen) {
                        scrollOffset += event.mouseWheelScroll.delta * 30.0f; // 30 est la vitesse de défilement
                        // Limitez scrollOffset si nécessaire
                    }

                    //// Gestion du défilement
                    //if (event.type == sf::Event::MouseWheelScrolled && isShopScreen) {
                    //    scrollOffset -= event.mouseWheelScroll.delta * 30.0f; // Ajustez ce facteur selon vos besoins

                    //    // Limitez scrollOffset pour éviter le défilement hors des limites
                    //    // Par exemple, si vous ne voulez pas défiler au-delà du premier ou du dernier élément
                    //    scrollOffset = std::max(scrollOffset, /* limite inférieure */);
                    //    scrollOffset = std::min(scrollOffset, /* limite supérieure */);
                    //}

                    // Mettre à jour la position Y des ShopItem en fonction de scrollOffset
                    for (auto& item : items) {
                        item.sprite.setPosition(item.sprite.getPosition().x, item.originalY + scrollOffset);
                        item.title.setPosition(item.title.getPosition().x, item.originalTitleY + scrollOffset);
                    }

                }
            }
        }



        if (clock.getElapsedTime().asSeconds() >= 1.0 / 24) {
            background.setTexture(textures[index]);

            // Mise à jour de l'index
            if (ascending) {
                if (index < X - 1) index++;
                else ascending = false;
            }
            else {
                if (index > 0) index--;
                else ascending = true;
            }

            clock.restart();
        }


        window.clear();
        window.draw(background);
        if (isMenuScreen) {
            window.draw(playButton);
            window.draw(settingsButton);
            window.draw(shop);
        }
        else if(isSettingsScreen){
            window.draw(Casier);
            window.draw(retour);
        }
        else if (isShopScreen) {
            window.draw(retour);
            // Dessinez les items
            for (auto& item : items) {
                window.draw(item.sprite);
                window.draw(item.title);
            }
        }
        window.display();
    }

    return 0;
}
