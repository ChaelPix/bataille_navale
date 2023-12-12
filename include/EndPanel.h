#pragma once

#include "EntityRectangle.h"
#include "EntityText.h"
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
	EntityText* scoreText;
	bool doShow;

public:

	EndPanel(sf::Font& font);

	void Show(bool isVictory, int score, int wonPoints);
	bool isLeaveButtonClicked(MouseManager mouse);
	void draw(sf::RenderWindow& window);
};

