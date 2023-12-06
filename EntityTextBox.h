#pragma once
#include "EntityRectangle.h"
#include "EntityText.h"
#include "Settings.h"
#include "WaitTimer.h"

class EntityTextBox : public Entity
{
private:
	EntityRectangle* textBackground;
	EntityRectangle* selectedBackground;
	EntityText* text;
	EntityText* defaultText;

	bool isSelected;
	sf::String inputText;
	TextBoxSettings textBoxSettings;
	sf::Clock cooldown;

public:

	EntityTextBox(sf::Vector2f position, sf::Texture*, sf::Font& font, std::string description);

	void update(sf::Event &event);
	void draw(sf::RenderWindow& window) override;

	bool isOnTextBox(sf::Vector2f pos);
	std::string getText();

	void setSelected(bool isSelected);
};

