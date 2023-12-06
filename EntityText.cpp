#include "EntityText.h"

EntityText::EntityText(sf::Font& font, sf::Vector2f position, int size, std::string text)
{
	Text.setFont(font);
	SetPosition(position);
	SetCharacterSize(size);
	SetText(text);
}

void EntityText::SetText(std::string txt)
{
	Text.setString(txt);
}

void EntityText::SetPosition(sf::Vector2f position)
{
	Text.setPosition(position);
}

void EntityText::SetPosition(float posX, float posY)
{
	Text.setPosition(sf::Vector2f(posX, posY));
}

void EntityText::SetCharacterSize(int size)
{
	Text.setCharacterSize(size);
}

void EntityText::SetColor(sf::Color color)
{
	Text.setColor(color);
}
