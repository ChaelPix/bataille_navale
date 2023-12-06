#include "EntityTextBox.h"

EntityTextBox::EntityTextBox(sf::Vector2f position, sf::Texture* texture, sf::Font &font, std::string description)
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

void EntityTextBox::update(sf::Event &event)
{
	if (!isSelected)
		return;

    if (cooldown.getElapsedTime().asMilliseconds() >= textBoxSettings.timeCooldownTyping)
    {
		cooldown.restart();
        if (event.type == sf::Event::TextEntered)
        {
            if(event.text.unicode == 8)
                inputText = inputText.substring(0, inputText.getSize() - 1);
            else if(event.text.unicode == 13)
                std::cout << "enter pressed" << std::endl;
            else
                inputText += event.text.unicode;

            text->SetText(inputText);
        }
    }

	//
	int characterSize = textBoxSettings.maxCharacterSize;
	text->SetCharacterSize(characterSize);
	while ((text->getWidth() > textBackground->getSize().x /*|| text->getHeight() > textBoxSettings.textBoxSize.y / 2.5*/) && characterSize > textBoxSettings.minCharacterSize)
	{
		characterSize--;
		text->SetCharacterSize(characterSize);
	}
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

void EntityTextBox::setSelected(bool isSelected)
{
	this->isSelected = isSelected;
}
