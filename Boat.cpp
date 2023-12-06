#include "Boat.h"

Boat::Boat(int id, CoreGame::boatTypes boatType, sf::Vector2f size, sf::Texture* texture) : EntityRectangle(size)
{
	boatId = id;
	this->boatType = boatType;
	this->isRotated = false;
	isPlaced = false;

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

void Boat::setSpawnPos(sf::Vector2f spawnPos)
{
	this->spawnPos = spawnPos;
}

void Boat::OnRelease(bool isGrid)
{
	if (!isGrid)
	{
		rotate(0);
		isRotated = false;
		this->setPosition(spawnPos);
	}

	setIsPlaced(isGrid);
}

bool Boat::isInGrid()
{
	GridSettings grid;
	sf::Vector2f pos = shape.getPosition();

	int width = 0;
	int height = 0;
	int offsetX = 0;

	int gridSize = grid.squareSize / grid.nbPixels;

	if (isRotated)
	{
		width = gridSize;
		offsetX = gridSize;
		height = shape.getSize().x;
	}
	else {
		width = shape.getSize().x;
		height = gridSize;
	}

	bool isInGrid = (pos.x - offsetX > grid.playerGridPosition.x
		&& pos.x + width - offsetX < grid.playerGridPosition.x + grid.squareSize + grid.boatTolerance)
		&& (pos.y > grid.playerGridPosition.y
			&& pos.y + height < grid.playerGridPosition.y + grid.squareSize + grid.boatTolerance);

	return isInGrid;
}

bool Boat::getIsPlaced()
{
	return isPlaced;
}

void Boat::setIsPlaced(bool isPlaced)
{
	this->isPlaced = isPlaced;
}

sf::Vector2f Boat::AnchoredPosition()
{
	GridSettings grid;
	int gridSize = grid.squareSize / grid.nbPixels;

	int anchoredX = shape.getPosition().x / gridSize;
	int anchoredY = shape.getPosition().y / gridSize;

	return sf::Vector2f(anchoredX, anchoredY);
}
