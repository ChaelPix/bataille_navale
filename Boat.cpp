#include "Boat.h"

Boat::Boat(int id, CoreGame::boatTypes boatType, sf::Vector2f size, sf::Texture* texture) : EntityRectangle(size)
{
	boatId = id;
	this->boatType = boatType;
	this->isRotated = false;
	isPlaced = false;

	if (texture != nullptr)
	{
		setTexture(texture);
	}

	gridSize = grid.squareSize / grid.nbPixels;
	indicator = new EntityRectangle(sf::Vector2f(0, 0));
	canBeDrop = false;
	isDragged = false;
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
	isDragged = false;
}

bool Boat::isInGrid()
{
	sf::Vector2f pos = shape.getPosition();

	int width = 0;
	int height = 0;
	int offsetX = 0;

	gridSize = grid.squareSize / grid.nbPixels;

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

void Boat::draw(sf::RenderWindow& window)
{
	if (isDragged)
	{
		sf::Vector2f boatPos = getPosition();
		sf::Vector2f boatSize = getSize();
		int gridSizex2 = gridSize * 2;

		if (isRotated)
		{
			indicator->setSize(sf::Vector2f(boatSize.y + gridSizex2, boatSize.x + gridSizex2));
			indicator->setPosition(sf::Vector2f(boatPos.x - gridSizex2, boatPos.y - gridSize));
		}
		else
		{
			indicator->setSize(sf::Vector2f(boatSize.x + gridSizex2, boatSize.y + gridSizex2));
			indicator->setPosition(sf::Vector2f(boatPos.x - gridSize, boatPos.y - gridSize));
		}

		indicator->draw(window);
	}

	EntityRectangle::draw(window);
}

void Boat::SetCanBeDrop(bool action)
{
	canBeDrop = action;

	if (canBeDrop)
	{
		indicator->setColor(sf::Color(0, 255, 0, 175));
	}
	else {
		indicator->setColor(sf::Color(255, 0, 0, 175));
	}
}

void Boat::SetIsDrag(bool action)
{
	isDragged = action;
}
