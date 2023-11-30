#pragma once
#include "EntityRectangle.h"
#include "CoreGame.h"
class Boat : public EntityRectangle
{

private : 
	int boatId;
	CoreGame::boatTypes boatType;

public :

	Boat(int id, CoreGame::boatTypes boatType, sf::Vector2f size, sf::Texture* texture = nullptr);

	int getBoatId();
	CoreGame::boatTypes getBoatType();

};

