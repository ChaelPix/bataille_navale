#pragma once
#include"EntityRectangle.h"
#include"Settings.h"
#include <cstdlib> // pour rand()

//class CloudManager {
//
//private:
//    std::vector<sf::Texture> cloudTextures;
//    std::vector<sf::Sprite> clouds;
//    std::vector<sf::Sprite> RandomCloudsVector;
//
//    //Cloud
//public:
//
//    CloudManager() {
//        // Charger les textures et créer les sprites
//        for (int i = 0; i < 5; i++) {
//            sf::Texture texture;
//            if(!texture.loadFromFile("ressources/UI/cloud.png"))
//                ; // Assurez-vous que ce chemin d'accès est correct
//            sf::Sprite sprite(texture);
//            sprite.setScale(0.2, 0.5);
//            sprite.setTexture(texture);
//            // Position initiale du sprite
//            sprite.setPosition(static_cast<float>(1300), static_cast<float>(600));
//
//            cloudTextures.push_back(texture);
//            clouds.push_back(sprite);
//        }
//
//        // Charger les textures et créer les sprites
//        for (int i = 0; i < 5; i++) {
//            sf::Texture randomTexture;
//            randomTexture.loadFromFile("ressources/UI/cloud.png"); // Assurez-vous que ce chemin d'accès est correct
//            sf::Sprite RadomCloudSprite(randomTexture);
//            RadomCloudSprite.setScale(0.2, 0.5);
//
//            // Position initiale du sprite
//            RadomCloudSprite.setPosition(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));
//
//            cloudTextures.push_back(randomTexture);
//            RandomCloudsVector.push_back(RadomCloudSprite);
//        }
//    }
//
//    void update() {
//        // Mettre à jour la position des nuages mobiles
//        for (size_t i = 0; i < RandomCloudsVector.size(); i++) {
//            sf::Vector2f position = RandomCloudsVector[i].getPosition();
//
//            // Logique de mouvement spécifique
//            if (position.x < -3000) {
//                int y = (rand() % 70) + 20;
//                RandomCloudsVector[i].setPosition(sf::Vector2f(1000, y));
//            }
//            RandomCloudsVector[i].move(-1.1, 0);
//
//        }
//    }
//
//    void draw(sf::RenderWindow& window) {
//        update();
//        // Dessiner les nuages
//        for (auto& cloud : clouds) {
//            window.draw(cloud);
//        }
//
//        // Dessiner les nuages
//        for (auto& Randcloud : RandomCloudsVector) {
//            window.draw(Randcloud);
//        }
//    }
//
//};
#include <iostream>

class CloudManager {

private:
    sf::Texture cloudTexture;
    std::vector<EntityRectangle> cloudsStatic;
    std::vector<sf::Sprite> clouds;
    std::vector<sf::Sprite> RandomCloudsVector;
    CloudSettings cloudSettings;
public:
    //buttons.push_back(EntityRectangle(menuButtonsSettings.buttonsSize, startPos, buttonsTextures[i * 2]));

    CloudManager() {
        // Charger les textures et créer les sprites
        cloudTexture.loadFromFile(cloudSettings.cloudImgPath);

        for (int i = 0; i < 40; i++) {
            cloudsStatic.push_back(EntityRectangle(cloudSettings.cloudSize, cloudSettings.cloudPosition[i], cloudTexture, cloudSettings.anglesDegres[i], cloudSettings.Origin));
            cloudsStatic.at(i).setTexture(&cloudTexture);
        }

        //// Charger les textures et créer les sprites
        //for (int i = 0; i < 5; i++) {
        //    sf::Texture randomTexture;
        //    randomTexture.loadFromFile("ressources/UI/cloud.png"); // Assurez-vous que ce chemin d'accès est correct
        //    sf::Sprite RadomCloudSprite(randomTexture);
        //    RadomCloudSprite.setScale(0.2, 0.5);

        //    // Position initiale du sprite
        //    RadomCloudSprite.setPosition(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));

        //    cloudTextures.push_back(randomTexture);
        //    RandomCloudsVector.push_back(RadomCloudSprite);
        //}
    }

    void update() {
        // Mettre à jour la position des nuages mobiles
        for (size_t i = 0; i < RandomCloudsVector.size(); i++) {
            sf::Vector2f position = RandomCloudsVector[i].getPosition();

            // Logique de mouvement spécifique
            if (position.x < -3000) {
                int y = (rand() % 70) + 20;
                RandomCloudsVector[i].setPosition(sf::Vector2f(1000, y));
            }
            RandomCloudsVector[i].move(-1.1, 0);

        }
    }

    void draw(sf::RenderWindow& window) {
        update();
        // Dessiner les nuages
        for (int i = 0; i < cloudsStatic.size(); i++)
        {
            cloudsStatic.at(i).draw(window); 
        }
        // Dessiner les nuages
 /*       for (auto& Randcloud : RandomCloudsVector) {
            Randcloud.draw(window);
        }*/
    }

};
