#include "EntityTextBox.h"

EntityTextBox::EntityTextBox(sf::Vector2f position, sf::Texture* texture, sf::Font &font, std::string description, int maxChar) : maxChar(maxChar)
{
	isSelected = false;
	inputText = "";

	if(texture != nullptr)
		textBackground = new EntityRectangle(textBoxSettings.textBoxSize, position, *texture);
	else
		textBackground = new EntityRectangle(textBoxSettings.textBoxSize, position);

	selectedBackground = new EntityRectangle(textBoxSettings.selectBoxSize, position + textBoxSettings.selectBoxOffset + sf::Vector2f(0, textBoxSettings.textBoxSize.y), textBoxSettings.selectBoxColor);
	
	text = new EntityText(font, position, textBoxSettings.maxCharacterSize, sf::Color::Black);
	defaultText = new EntityText(font, position, textBoxSettings.maxCharacterSize, textBoxSettings.defaultTextColor);
	defaultText->SetText(description);
}

bool EntityTextBox::update(sf::Event &event)
{
	if (!isSelected)
		return false;

	if (event.type == sf::Event::TextEntered)
	{
		if (isPressed)
			return false;

		if (event.text.unicode == 8)
			inputText = inputText.substring(0, inputText.getSize() - 1);
		else if (event.text.unicode == 13)
			return true;
		else if (inputText.getSize() < maxChar)
			inputText += event.text.unicode;

		text->SetText(inputText);
		isPressed = true;
	}
	else
		isPressed = false;
	

	//
	int characterSize = textBoxSettings.maxCharacterSize;
	text->SetCharacterSize(characterSize);
	while ((text->getWidth() > textBackground->getSize().x) && characterSize > textBoxSettings.minCharacterSize)
	{
		characterSize--;
		text->SetCharacterSize(characterSize);
	}

	return false;
}

void EntityTextBox::draw(sf::RenderWindow& window)
{
	textBackground->draw(window);

	if(isSelected)
		selectedBackground->draw(window);

	text->draw(window);
	
	if (inputText.isEmpty())
		defaultText->draw(window);
}

bool EntityTextBox::isOnTextBox(sf::Vector2f pos)
{
	return textBackground->getShape().getGlobalBounds().contains(pos);
}

std::string EntityTextBox::getText()
{
	return inputText;
}

void EntityTextBox::clearText()
{
	inputText = "";
	text->SetText("");
}

void EntityTextBox::setText(std::string txt)
{
	inputText = txt;
	text->SetText(txt);
}

void EntityTextBox::setSelected(bool isSelected)
{
	this->isSelected = isSelected;
}
