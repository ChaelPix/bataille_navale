#include "CursorCellSelector.h"

bool CursorCellSelector::isOnEnnemyGrid(sf::Vector2f pos)
{
	
	int gridSize = grid.squareSize / grid.nbPixels;

	bool isInGrid = (pos.x > grid.ennemyGridPosition.x
		&& pos.x < grid.ennemyGridPosition.x + grid.squareSize + grid.boatTolerance)
		&& (pos.y > grid.ennemyGridPosition.y
		&& pos.y  < grid.ennemyGridPosition.y + grid.squareSize + grid.boatTolerance);

	return isInGrid;
}

CursorCellSelector::CursorCellSelector(BattleshipCore& battleshipCore)
{
	this->battleshipCore = &battleshipCore;

	GridSettings grid;
	int gridSize = grid.squareSize / grid.nbPixels;

	
}

void CursorCellSelector::draw(sf::RenderWindow window, MouseManager& mouse)
{
	if (isOnEnnemyGrid(mouse.getClickPosition()))
	{

	}
}
