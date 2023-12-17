#include "GameMessage.h"

GameMessage::GameMessage(sf::Font& font, sf::Vector2f pos, std::string message, std::string playerName, bool isEnemy)
{
	nameTxt = new EntityText(font, pos, chatSettings.nameFSize, playerName, isEnemy ? chatSettings.nameEColor : chatSettings.namePColor);
	messageTxt = new EntityText(font, pos + chatSettings.messageOffsetFromName, chatSettings.messageFSize, message, chatSettings.messageColor);
}

GameMessage::~GameMessage()
{
	delete nameTxt;
	delete messageTxt;
}

void GameMessage::draw(sf::RenderWindow& window)
{
	nameTxt->draw(window);
	messageTxt->draw(window);
}

void GameMessage::UpdatePosition(sf::Vector2f pos)
{
	nameTxt->SetPosition(pos);
	messageTxt->SetPosition(pos + chatSettings.messageOffsetFromName);
}
