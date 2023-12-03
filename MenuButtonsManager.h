#pragma once

#include "EntityRectangle.h"
#include "MouseManager.h"

class MenuButtonsManager
{
private:
	std::vector<EntityRectangle> buttons;

	const int nbButtons = 3;
	const int nbTextures = 6;
	sf::Texture buttonsTextures[6];

public:
	MenuButtonsManager();

	void drawButtons(sf::RenderWindow& window);
	void CheckButtonHover(MouseManager& mouse);
};

