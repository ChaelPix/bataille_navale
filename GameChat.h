#pragma once

#include "EntityTextBox.h"
#include "Settings.h"
#include "TCPClient.h"

class GameChat
{
private:
	TCPClient* client;

	EntityTextBox* textBox;
	std::vector<std::string> playerMessages;
	std::vector<std::string> enemyMessages;

	std::vector<EntityText> texts;
	EntityRectangle* background;

	WindowSettings windowSettings;


public:

	GameChat(TCPClient* client);

	void Update();
	void Draw(sf::RenderWindow& window);

};

