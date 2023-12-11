#include "GameChat.h"

GameChat::GameChat(TCPClient* client, sf::Font& font, std::string playerName, std::string enemyName) : client(client), font(font), playerName(playerName), enemyName(enemyName)
{
	EndMenuSettings ems;
	int bgSizeX = windowSettings.gameWindowSize.x - ems.panelSize.x;
	background = new EntityRectangle(gameChatSettings.chatSize, gameChatSettings.chatPos, sf::Color(0, 0, 0, 200));

	textBox = new EntityTextBox(gameChatSettings.chatPos + gameChatSettings.textBoxPosFromChat, nullptr, font, "Message Here");
	textBox->setSelected(true);
}

void GameChat::Update(sf::Event& event)
{
	if (textBox->update(event) && textBox->getText() != "")
	{
		createMessage(textBox->getText(), false);
		client->sendMessage("M" + textBox->getText());

		textBox->clearText();
	}
}

void GameChat::Draw(sf::RenderWindow& window)
{
	background->draw(window);
	textBox->draw(window);

	for (int i = 0; i < gameMessages.size(); i++)
		gameMessages.at(i)->draw(window);

}

void GameChat::ReceiveMessage(std::string message)
{
	std::string msg = message.erase(0, 1);
	createMessage(msg, true);
}

void GameChat::createMessage(std::string msg, bool isEnemy)
{
	std::string name = "";
	isEnemy ? name = enemyName : name = playerName;

	sf::Vector2f pos = (gameChatSettings.chatPos + gameChatSettings.textBoxPosFromChat) + gameChatSettings.firsMessagePosFromtxtBox;

	gameMessages.insert(gameMessages.begin(), new GameMessage(font, pos, msg, name, isEnemy));
	for (int i = gameMessages.size() - 1; i >= 0; i--)
	{
		sf::Vector2f newPos = pos - (sf::Vector2f(0, (gameChatSettings.messageSize.y + gameChatSettings.messageOffset.y) * i));
		if (newPos.y > gameChatSettings.maxY)
		{
			gameMessages.at(i)->UpdatePosition(newPos);
		}
		else
		{
			gameMessages.erase(gameMessages.begin() + i);
		}
	}
}