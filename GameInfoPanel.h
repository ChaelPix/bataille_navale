#pragma once

#include "EntityText.h"
#include "EntityRectangle.h"
#include "Settings.h"
#include <sstream>
class GameInfoPanel
{
private:
		GameMenuSettings gameMenuSettings;

		EntityRectangle* background;
		sf::Texture backgroundTexture;

		EntityText* timerTxt;
		EntityText* turnTxt;
		EntityText* infoTxt;

		std::vector<Entity*> toDraw;
public:
		GameInfoPanel(sf::Font& font);

		void updateTimer(float time);
		void updateTurn(int turn);
		void updateGameInfo(std::string info);

		void draw(sf::RenderWindow& window);
};

