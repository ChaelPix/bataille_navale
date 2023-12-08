#include "CursorCellSelector.h"

bool CursorCellSelector::isOnEnnemyGrid(sf::Vector2f pos)
{
	int gridSize = grid.squareSize / grid.nbPixels;

	bool isInGrid = (pos.x > grid.ennemyGridPosition.x
		&& pos.x < grid.ennemyGridPosition.x + grid.squareSize)
		&& (pos.y > grid.ennemyGridPosition.y
		&& pos.y  < grid.ennemyGridPosition.y + grid.squareSize);

    doDraw = isInGrid;

	return isInGrid;
}

CursorCellSelector::CursorCellSelector(BattleshipCore& battleshipCore, TCPClient* client)
{
	this->client = client;
	this->canHit = false;
	this->battleshipCore = &battleshipCore;

	GridSettings grid;
	int gridSize = grid.squareSize / grid.nbPixels;

	cursor = new EntityRectangle(sf::Vector2f(gridSize, gridSize), sf::Vector2f(0, 0), sf::Color(0, 255, 0, 125));
}


CursorCellSelector::State CursorCellSelector::update(MouseManager& mouse)
{
    if (isBusy)
        return State::Nothing;

    sf::Vector2f mousePos = mouse.getClickPosition();

    if (!isOnEnnemyGrid(mousePos))
        return State::Nothing;

    updateCursorSelection(mousePos);

    if (canHit && mouse.isMouseClicked())
    {
        return handleAttack();
    }

    return State::Nothing;
}

void CursorCellSelector::updateCursorSelection(const sf::Vector2f& mousePos)
{
    int gridSize = grid.squareSize / grid.nbPixels;
    anchoredX = (mousePos.x - grid.ennemyGridPosition.x) / gridSize;
    anchoredY = (mousePos.y - grid.ennemyGridPosition.y) / gridSize;
    cursor->setPosition(grid.ennemyGridPosition.x + anchoredX * gridSize, grid.ennemyGridPosition.y + anchoredY * gridSize);
    updateCursorColor();
}

void CursorCellSelector::updateCursorColor()
{
    switch (battleshipCore->getTargetCellType(anchoredY, anchoredX))
    {
    case BattleshipCore::CellType::hit:
    case BattleshipCore::CellType::water:
        canHit = false;
        cursor->setColor(sf::Color(255, 0, 0, 125));
        break;

    default:
        canHit = true;
        cursor->setColor(sf::Color(0, 255, 0, 125));
    }
}

CursorCellSelector::State CursorCellSelector::handleAttack()
{
    isBusy = true;

    client->sendMessage(battleshipCore->serializeAttack(anchoredX, anchoredY));

    BattleshipCore::CellType attackResult = battleshipCore->Attack(anchoredY, anchoredX, true);

    //hit nothing
    if (attackResult == BattleshipCore::CellType::water) {
        isBusy = false;
        return State::Attacked;
    }

    //hit a boat, check if down
    if (battleshipCore->CheckIfBoatDown(anchoredY, anchoredX, true)) {
        isBusy = false;
        return battleshipCore->areAllEnnemyBoatsDown() ? State::Win : State::ExtraTurn;
    }

    //only hit
    isBusy = false;
    return State::ExtraTurn;
}


void CursorCellSelector::draw(sf::RenderWindow& window)
{
    if(doDraw)
	    cursor->draw(window);
}
