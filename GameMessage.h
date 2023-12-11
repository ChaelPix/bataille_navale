#pragma once

#include "Settings.h"
#include "EntityText.h"
#include "EntityCircle.h"

class GameMessage
{
private:
	EntityText* nameTxt;
	EntityText* messageTxt;
	GameChatSettings chatSettings;

public:
	GameMessage(sf::Font& font, sf::Vector2f pos, std::string message, std::string playerName, bool isEnemy);
	~GameMessage();

	void draw(sf::RenderWindow& window);
	void UpdatePosition(sf::Vector2f pos);
};

