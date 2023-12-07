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

	cursor = new EntityRectangle(sf::Vector2f(gridSize, gridSize), sf::Vector2f(0, 0), sf::Color(0, 255, 0, 125));
}

void CursorCellSelector::draw(sf::RenderWindow& window, MouseManager& mouse)
{
	sf::Vector2f mousePos = mouse.getClickPosition();

	if (isOnEnnemyGrid(mousePos))
	{
		int gridSize = grid.squareSize / grid.nbPixels;

		int anchoredX = (mousePos.x - grid.ennemyGridPosition.x) / gridSize;
		int anchoredY = (mousePos.y - grid.ennemyGridPosition.y) / gridSize;

		cursor->setPosition(grid.ennemyGridPosition.x + anchoredX * gridSize, grid.ennemyGridPosition.y + anchoredY * gridSize);

		if (battleshipCore->isTargetCellEmpty(anchoredX, anchoredY))
			cursor->setColor(sf::Color(0, 255, 0, 125));
		else
			cursor->setColor(sf::Color(255, 0, 0, 125));

		cursor->draw(window);
	}
}
