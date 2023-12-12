#pragma once

#include "Boat.h"
#include "Settings.h"
#include "MouseManager.h"
#include "BattleshipCore.h"
#include <SFML/Graphics.hpp>


class PlayerBoatsManager
{
private:
	std::vector<BattleshipCore::boatTypes> boatsType;
	std::vector<Boat> boatsList;
	sf::Texture boatTextures[4];

	BattleshipCore* battleshipCore;
	Boat* selectedBoat = nullptr;
	void InstiantiateBoats(int bottomGridOffset);

	int rotateCooldown;
	unsigned int cooldown;
	bool isBoatInGrid = false;
	bool isBoatPlacementOk = false;

public:
	PlayerBoatsManager(BattleshipCore* gameCore = nullptr, int bottomGridOffset = 50);
	void draw(sf::RenderWindow& window);
	void dragBoats(MouseManager &mouseManager);

	void UnselectBoat();
	void RandomPlacement();

private:
	int getTextureIndex(BattleshipCore::boatTypes type);
};

