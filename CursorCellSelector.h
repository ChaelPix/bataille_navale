#pragma once

#include "EntityRectangle.h"
#include "MouseManager.h"
#include "BattleshipCore.h"

class CursorCellSelector
{

private:
	EntityRectangle* cursor;
	BattleshipCore* battleshipCore;
	GridSettings grid;

	bool isOnEnnemyGrid(sf::Vector2f mousePos);

public:

	CursorCellSelector(BattleshipCore &battleshipCore);

	void draw(sf::RenderWindow window, MouseManager& mouse);

};

