#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual void draw(sf::RenderWindow& window) = 0; // M�thode purement virtuelle pour dessiner l'entit�.
    virtual void update() = 0; // M�thode pour mettre � jour l'entit�.

    // Autres m�thodes communes (positionnement, rotation, etc.)


    virtual ~Entity() {} // Destructeur virtuel
};
