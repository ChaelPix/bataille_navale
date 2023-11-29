//dans boat.h
#pragma once
#include "EntityRectangle.h"
#include "CoreGame.h"
class Boat : public EntityRectangle {
private:
    int boatId;
    CoreGame::typeBateau boatType;
    int direction; // 0 pour horizontal, 1 pour vertical

public:
    Boat(int id, CoreGame::typeBateau boatType, sf::Vector2f size, sf::Texture* texture = nullptr);

    int getBoatId();
    CoreGame::typeBateau getBoatType();
    int getDirection() const { return direction; }
    void setDirection(int newDirection) { direction = newDirection; }
    sf::FloatRect getGlobalBounds() const {
        // Supposons que EntityRectangle hérite de sf::RectangleShape
        return this->getGlobalBounds(); // Utiliser la méthode getGlobalBounds() de sf::RectangleShape
    }

    sf::Vector2f getSize() const {
        // Supposons que EntityRectangle hérite de sf::RectangleShape
        return this->getSize(); // Utiliser la méthode getSize() de sf::RectangleShape
    }

};
