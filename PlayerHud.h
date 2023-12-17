#pragma once

#include "EntityRectangle.h"
#include "EntityText.h"
#include "EntityCircle.h"
#include "Settings.h"

class PlayerHud
{
private:
	PlayerHUDSettings playerHudSettings;

	EntityRectangle* background;
	sf::Texture bgTexture;

	EntityCircle* playerPicture;
	EntityText* nameTxt;
	EntityText* kdTxt;
	EntityText* scoreTxt;
	bool isEnemy;
	sf::Clock* clock;
	bool istxtok = false;
public:

	PlayerHud(sf::Font& font, bool isEnemy, std::string name, std::string kd, std::string score, sf::Texture& playerPicture);

	void draw(sf::RenderWindow& window);
	void InitEnemyTxt();
};

