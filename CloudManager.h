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
    sf::Texture cloudTextureAnimate;
    std::vector<EntityRectangle> cloudsStatic;
    std::vector<EntityRectangle> cloudsStaticAnimate;
    std::vector<sf::Sprite> clouds;
    std::vector<sf::Sprite> RandomCloudsVector;
    CloudSettings cloudSettings;

    //TEST EXPLOSION
    float explosionOpacity;
    float opacityChangeSpeed; // Vitesse de changement d'opacité
    sf::Texture explosionTestTexture;
    std::vector<EntityRectangle> explosionTestVector;

public:
    //buttons.push_back(EntityRectangle(menuButtonsSettings.buttonsSize, startPos, buttonsTextures[i * 2]));

    CloudManager() {
        // Charger les textures et créer les sprites
        cloudTexture.loadFromFile(cloudSettings.cloudImgPath2);
        cloudTextureAnimate.loadFromFile(cloudSettings.cloudImgPath);

        WindowSettings ws;
        for (int i = 0; i < 2; i++) {
            cloudsStatic.push_back(EntityRectangle(ws.gameWindowSize, sf::Vector2f(0, 0), cloudTexture, sf::Color(255, 255, 255, 110)));
            cloudsStatic.at(i).setTexture(&cloudTexture);
        }

    
        for (int i = 0; i < 2; i++)
        {
            cloudsStaticAnimate.push_back(EntityRectangle(cloudSettings.cloudSize, cloudSettings.cloudPositionAnimate[i], cloudTextureAnimate, sf::Color(255, 255, 255, 172)));
            cloudsStaticAnimate.at(i).setTexture(&cloudTextureAnimate);
        }


        //TEST EXPLOSION
        explosionTestTexture.loadFromFile("ressources/UI/expl2.png");
        explosionTestVector.push_back(EntityRectangle(sf::Vector2f(80, 80), sf::Vector2f(780, 430), explosionTestTexture, sf::Color(255, 255, 255, 172)));
        explosionTestVector.at(0).setTexture(&explosionTestTexture);
        explosionOpacity = 255; // Valeur initiale de l'opacité
        opacityChangeSpeed = 0.06f; // Ajustez cette valeur pour changer la vitesse de pulsation


        //for (int i = 0; i < 40; i++) {
        //    cloudsStatic.push_back(EntityRectangle(cloudSettings.cloudSize, cloudSettings.cloudPosition[i], cloudTexture, cloudSettings.anglesDegres[i], cloudSettings.Origin));
        //    cloudsStatic.at(i).setTexture(&cloudTexture);
        //}

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
        for (size_t i = 0; i < cloudsStaticAnimate.size(); i++) {
            sf::Vector2f position = cloudsStaticAnimate[i].getPosition();

            // Logique de mouvement spécifique
            if (position.x < -2500) {
                cloudsStaticAnimate[i].setPosition(sf::Vector2f(1000, -400));
            }
            cloudsStaticAnimate[i].move(-0.025, 0);

        }

        //TEST EXPLOSION
        // Mise à jour de l'opacité pour l'effet de battement de coeur
        explosionOpacity += opacityChangeSpeed;
        if (explosionOpacity > 255 || explosionOpacity < 86) {
            opacityChangeSpeed = -opacityChangeSpeed; // Inversez la direction lorsque les limites sont atteintes
            explosionOpacity = std::max(86.0f, std::min(255.0f, explosionOpacity)); // Gardez l'opacité dans la plage [0, 255]
        }
        // Appliquer l'opacité modifiée à votre sprite d'explosion
        for (auto& explosion : explosionTestVector) {
            sf::Color currentColor = sf::Color(255, 255, 255, 172);
            currentColor.a = static_cast<sf::Uint8>(explosionOpacity);
            explosion.setColor(currentColor);
        }
    }

    void draw(sf::RenderWindow& window) {
        update();

        //TEST EXPLOSION
        explosionTestVector.at(0).draw(window);

        // Dessiner les nuages
        for (int i = 0; i < cloudsStatic.size(); i++)
        {
            cloudsStatic.at(i).draw(window); 
        }
        // Dessiner les nuages
        for (int i = 0; i < cloudsStaticAnimate.size(); i++)
        {
            cloudsStaticAnimate.at(i).draw(window);
        }
        
        // Dessiner les nuages
 /*       for (auto& Randcloud : RandomCloudsVector) {
            Randcloud.draw(window);
        }*/
    }

};
