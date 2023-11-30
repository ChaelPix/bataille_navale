#pragma once

#include "Boat.h"
#include "CoreGame.h"
#include "Settings.h"
#include <SFML/Graphics.hpp>

class PlayerBoatsManager
{
private:
	std::vector<CoreGame::boatTypes> boatsType;
	std::vector<Boat> boatsList;

	Boat* selectedBoat = nullptr;
	void InstiantiateBoats(int bottomGridOffset);

public:
	PlayerBoatsManager(int bottomGridOffset = 50);
	void draw(sf::RenderWindow& window);
};

