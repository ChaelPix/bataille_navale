#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual void draw(sf::RenderWindow& window) = 0; // Méthode purement virtuelle pour dessiner l'entité.
    virtual void update() = 0; // Méthode pour mettre à jour l'entité.

    // Autres méthodes communes (positionnement, rotation, etc.)


    virtual ~Entity() {} // Destructeur virtuel
};
