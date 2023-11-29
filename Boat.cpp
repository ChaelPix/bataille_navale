//dans boat.cpp
#include "Boat.h"

Boat::Boat(int id, CoreGame::typeBateau boatType, sf::Vector2f size, sf::Texture* texture)
    : EntityRectangle(size), boatId(id), boatType(boatType), direction(0) { // Initialisation de la direction à 0 (horizontal)
    if (texture != nullptr) {
        setTexture(texture);
    }
}


int Boat::getBoatId()
{
	return this->boatId;
}

CoreGame::typeBateau Boat::getBoatType()
{
	return this->boatType;
}
