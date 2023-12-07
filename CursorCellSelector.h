#pragma once

#include "EntityRectangle.h"
#include "MouseManager.h"
#include "BattleshipCore.h"
#include "TCPClient.h"

class CursorCellSelector
{
public: 
	enum class State {
		Nothing,
		Attacked,
		Win,
		ExtraTurn
	};

private:
	EntityRectangle* cursor;
	BattleshipCore* battleshipCore;
	GridSettings grid;
	TCPClient* client;

	int anchoredX;
	int anchoredY;
	bool canHit;
	bool isBusy = false;
	bool doDraw = false;
	bool isOnEnnemyGrid(sf::Vector2f mousePos);

	void updateCursorSelection(const sf::Vector2f& mousePos);
	void updateCursorColor();
	State handleAttack();
public:

	CursorCellSelector(BattleshipCore &battleshipCore, TCPClient* client);

	State update(MouseManager& mouse);
	void draw(sf::RenderWindow& window);

};

