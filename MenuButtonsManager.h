#pragma once

#include "EntityRectangle.h"
#include "MouseManager.h"
#include "WaitTimer.h"
#include "EntityText.h"

class MenuButtonsManager
{
private:
	WaitTimer* timer;

	std::vector<EntityRectangle> buttons;

	const int nbButtons = 3;
	const int nbTextures = 8;
	sf::Texture buttonsTextures[8];
	EntityText* matchmakingText;

	bool isMatchMaking = false;
	int nbPoints;

	bool ButtonClickAction(int btnId);
	void updateMatchmakingTxt();

public:
	MenuButtonsManager(sf::Font & font);

	void draw(sf::RenderWindow& window);
	bool CheckButtonHover(MouseManager& mouse);

	bool getIsMatchMaking();
	void setIsMatchMaking(bool action);
};

