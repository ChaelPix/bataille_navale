#pragma once

#include "EntityRectangle.h"
#include "MouseManager.h"
#include "Settings.h"

class EndPanel
{
private:
	EntityRectangle* panel;
	EntityRectangle* endImage;
	EntityRectangle* leaveButton;
	sf::Texture imagesTextures[2];
	sf::Texture buttonTextures[2];
	EndMenuSettings endMenuSettings;

	bool doShow;

public:

	EndPanel();

	void Show(bool isVictory);
	bool isLeaveButtonClicked(MouseManager mouse);
	void draw(sf::RenderWindow& window);
};

