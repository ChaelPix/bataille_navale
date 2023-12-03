#pragma once

#include "EntityRectangle.h"
#include "MouseManager.h"

class MenuButtonsManager
{
private:
	std::vector<Entity*> buttons;

	sf::Texture buttonsTextures[6];

public:
	MenuButtonsManager();

	void drawButtons(sf::RenderWindow& window);
	void CheckButtonHover(const MouseManager& mouse);
};

