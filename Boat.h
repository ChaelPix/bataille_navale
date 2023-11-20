#pragma once
#include "EntityRectangle.h"
#include "CoreGame.h"
class Boat : public EntityRectangle
{

private : 
	int boatId;
	CoreGame::typeBateau boatType;

public :

	Boat(int id, CoreGame::typeBateau boatType, sf::Vector2f size, sf::Texture* texture = nullptr);

	int getBoatId();
	CoreGame::typeBateau getBoatType();

};

