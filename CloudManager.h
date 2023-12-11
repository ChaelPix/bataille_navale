#pragma once
#include"EntityRectangle.h"
#include"Settings.h"
#include <cstdlib> 

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
        //explosionTestTexture.loadFromFile("ressources/UI/expl2.png");
        //explosionTestVector.push_back(EntityRectangle(sf::Vector2f(80, 80), sf::Vector2f(780, 430), explosionTestTexture, sf::Color(255, 255, 255, 172)));
        //explosionTestVector.at(0).setTexture(&explosionTestTexture);
        //explosionOpacity = 255; // Valeur initiale de l'opacité
        //opacityChangeSpeed = cloudSettings.explodeOpacitySpeed; // Ajustez cette valeur pour changer la vitesse de pulsation
    }

    void update() {
        // Mettre à jour la position des nuages mobiles
        for (size_t i = 0; i < cloudsStaticAnimate.size(); i++) {
            sf::Vector2f position = cloudsStaticAnimate[i].getPosition();

            // Logique de mouvement spécifique
            if (position.x < -2500) {
                cloudsStaticAnimate[i].setPosition(sf::Vector2f(1000, -400));
            }
            cloudsStaticAnimate[i].move(-0.040, 0);

        }

        //TEST EXPLOSION
        
        // Mise à jour de l'opacité pour l'effet de battement de coeur
        //explosionOpacity += opacityChangeSpeed;
        //if (explosionOpacity > 255 || explosionOpacity < cloudSettings.minExplodeOpacity) {
        //    opacityChangeSpeed = -opacityChangeSpeed; // Inversez la direction lorsque les limites sont atteintes
        //    explosionOpacity = std::max(cloudSettings.minExplodeOpacity, std::min(255.0f, explosionOpacity)); // Gardez l'opacité dans la plage [0, 255]
        //}
        //// Appliquer l'opacité modifiée à votre sprite d'explosion
        //for (auto& explosion : explosionTestVector) {
        //    sf::Color currentColor = sf::Color(255, 255, 255, 172);
        //    currentColor.a = static_cast<sf::Uint8>(explosionOpacity);
        //    explosion.setColor(currentColor);
        //}
    }

    void draw(sf::RenderWindow& window) {
        update();

        //TEST EXPLOSION
       //explosionTestVector.at(0).draw(window);

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
        
    }

};
