#pragma once
#include "EntityRectangle.h"
#include "CoreGame.h"
#include "Settings.h"
#include <SFML/Graphics.hpp>

class Boat : public EntityRectangle
{

private:
	int boatId;
	CoreGame::boatTypes boatType;
	bool isRotated;
	bool canBeRotated;
	sf::Vector2f spawnPos;
	bool isPlaced;

public:

	Boat(int id, CoreGame::boatTypes boatType, sf::Vector2f size, sf::Texture* texture = nullptr);

	int getBoatId();
	CoreGame::boatTypes getBoatType();

	bool getIsRotated();
	void setRotated(bool state);

	void setSpawnPos(sf::Vector2f spawnPos);
	void OnRelease(bool isGrid);
	bool isInGrid();

	bool getIsPlaced();
	void setIsPlaced(bool isPlaced);

	sf::Vector2f AnchoredPosition();
};

