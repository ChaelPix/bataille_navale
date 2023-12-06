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

	bool isSelected;
	sf::String inputText;
	TextBoxSettings textBoxSettings;
	sf::Clock cooldown;

public:

	EntityTextBox(sf::Vector2f position, sf::Texture*, sf::Font& font);

	void update(sf::Event &event);
	void draw(sf::RenderWindow& window) override;

};

