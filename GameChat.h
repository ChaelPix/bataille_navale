#pragma once

#include "EntityTextBox.h"
#include "Settings.h"
#include "TCPClient.h"
#include "GameMessage.h"

class GameChat
{
private:
	TCPClient* client;

	EntityTextBox* textBox;
	std::vector<std::string> playerMessages;
	std::vector<std::string> enemyMessages;
	EntityRectangle* background;

	WindowSettings windowSettings;
	GameChatSettings gameChatSettings;

	std::vector<GameMessage*> gameMessages;

	sf::Font& font;
	std::string playerName;
	std::string enemyName;

	void createMessage(std::string msg, bool isEnemy);

public:

	GameChat(TCPClient* client, sf::Font& font, std::string playerName, std::string enemyName);

	void Update(sf::Event& event);
	void Draw(sf::RenderWindow& window);

	void ReceiveMessage(std::string message);
};

