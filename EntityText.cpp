#include "EntityText.h"

EntityText::EntityText(sf::Font& font, int size, std::string text)
{
	Text.setFont(font);
	SetCharacterSize(size);
	SetText(text);
}
EntityText::EntityText(sf::Font& font, const sf::Vector2f position, const int size, std::string text)
{
	Text.setFont(font);
	SetPosition(position);
	SetCharacterSize(size);
	SetText(text);
}
EntityText::EntityText(sf::Font& font, const sf::Vector2f position, const int size, sf::Color color)
{
	Text.setFont(font);
	SetPosition(position);
	SetCharacterSize(size);
	SetColor(color);
}
EntityText::EntityText(sf::Font& font, const sf::Vector2f position, const int size, std::string text, sf::Color color)
{
	Text.setFont(font);
	SetPosition(position);
	SetCharacterSize(size);
	SetColor(color);
	SetText(text);
}
void EntityText::SetText(std::string txt)
{
	Text.setString(txt);
}

void EntityText::SetTextAndCenter(std::string txt)
{
	SetText(txt);
	Text.setOrigin(sf::Vector2f(Text.getLocalBounds().width / 2, Text.getLocalBounds().height / 2));
}

void EntityText::SetTextAndCenterX(std::string txt)
{
	SetText(txt);
	Text.setOrigin(sf::Vector2f(Text.getLocalBounds().width / 2, 0));
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
	Text.setFillColor(color);
}

void EntityText::draw(sf::RenderWindow& window)
{
	window.draw(Text);
}

sf::Text EntityText::getText()
{
	return Text;
}

float EntityText::getWidth()
{
	return Text.getLocalBounds().width;
}

float EntityText::getHeight()
{
	return Text.getLocalBounds().height;
}
