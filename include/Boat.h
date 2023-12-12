#pragma once
#include "EntityRectangle.h"
#include "Settings.h"
#include "BattleshipCore.h"
#include <SFML/Graphics.hpp>

class Boat : public EntityRectangle
{

private:
	int boatId;
	BattleshipCore::boatTypes boatType;
	bool isRotated;
	bool canBeRotated;
	sf::Vector2f spawnPos;
	bool isPlaced;

	EntityRectangle* indicator;
	GridSettings grid;
	int gridSize;
	bool canBeDrop;
	bool isDragged;

public:

	Boat(int id, BattleshipCore::boatTypes boatType, sf::Vector2f size, sf::Texture* texture = nullptr);

	int getBoatId();
	BattleshipCore::boatTypes getBoatType();

	bool getIsRotated();
	void setRotated(bool state);

	void setSpawnPos(sf::Vector2f spawnPos);
	void OnRelease(bool isGrid);
	bool isInGrid();

	bool getIsPlaced();
	void setIsPlaced(bool isPlaced);

	sf::Vector2f AnchoredPosition();

	void draw(sf::RenderWindow& window) override;

	void SetCanBeDrop(bool action);
	void SetIsDrag(bool action);
};

