#pragma once

#include "EntityRectangle.h"
#include "MouseManager.h"
#include "WaitTimer.h"

class MenuButtonsManager
{
private:
	WaitTimer* timer;

	std::vector<EntityRectangle> buttons;

	const int nbButtons = 3;
	const int nbTextures = 8;
	sf::Texture buttonsTextures[8];

	sf::Font font;
	sf::Text matchmakingText;

	bool isMatchMaking = false;
	int nbPoints;

	void ButtonClickAction(int btnId);
	void updateMatchmakingTxt();

public:
	MenuButtonsManager();

	void draw(sf::RenderWindow& window);
	void CheckButtonHover(MouseManager& mouse);
};

