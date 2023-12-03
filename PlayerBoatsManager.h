#pragma once

#include "Boat.h"
#include "CoreGame.h"
#include "Settings.h"
#include "MouseManager.h"
#include <SFML/Graphics.hpp>

class PlayerBoatsManager
{
private:
	std::vector<CoreGame::boatTypes> boatsType;
	std::vector<Boat> boatsList;
	sf::Texture boatTextures[4];

	Boat* selectedBoat = nullptr;
	void InstiantiateBoats(int bottomGridOffset);

	int rotateCooldown;
	unsigned int cooldown;
	bool isBoatInGrid = false;

public:
	PlayerBoatsManager(int bottomGridOffset = 50);
	void draw(sf::RenderWindow& window);
	void dragBoats(MouseManager &mouseManager);

private:
	int getTextureIndex(CoreGame::boatTypes type);
};

