#include "Boat.h"

Boat::Boat(int id, CoreGame::typeBateau boatType, sf::Vector2f size, sf::Texture* texture) : EntityRectangle(size)
{
	boatId = id;
	this->boatType = boatType;

	if (texture != nullptr)
		setTexture(texture);
}
