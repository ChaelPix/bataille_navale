#include "GameChat.h"

GameChat::GameChat(TCPClient* client)
{
	EndMenuSettings ems;
	int bgSizeX = windowSettings.gameWindowSize.x - ems.panelSize.x;
	background = new EntityRectangle(sf::Vector2f(bgSizeX, windowSettings.gameWindowSize.y), sf::Vector2f(bgSizeX, 0), sf::Color(0, 0, 0, 200));
}

void GameChat::Update()
{

}

void GameChat::Draw(sf::RenderWindow& window)
{
	background->draw(window);
	textBox->draw(window);

	for (int i = 0; i < texts.size(); i++)
		texts.at(i).draw(window);
}
