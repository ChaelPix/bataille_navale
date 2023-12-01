#include "Boat.h"

Boat::Boat(int id, CoreGame::boatTypes boatType, sf::Vector2f size, sf::Texture* texture) : EntityRectangle(size)
{
	boatId = id;
	this->boatType = boatType;

	if (texture != nullptr)
		setTexture(texture);
}

int Boat::getBoatId()
{
	return this->boatId;
}

CoreGame::boatTypes Boat::getBoatType()
{
	return this->boatType;
}

bool Boat::getIsRotated()
{
	return isRotated;
}

void Boat::setRotated(bool state)
{
	isRotated = state;
}
