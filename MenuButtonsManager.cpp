#include "MenuButtonsManager.h"
#include <iostream>

MenuButtonsManager::MenuButtonsManager()
{
	MenuButtonsSettings menuButtonsSettings;

	for (int i = 0; i < nbTextures; i++)
	{
		buttonsTextures[i].loadFromFile(menuButtonsSettings.buttonImagePaths[i]);
	}

	sf::Vector2f startPos = menuButtonsSettings.buttonsStartPos;
	for (int i = 0; i < nbButtons; i++)
	{
		buttons.push_back(EntityRectangle(menuButtonsSettings.buttonsSize, startPos, buttonsTextures[i * 2]));
		startPos.y += menuButtonsSettings.buttonsSize.y + menuButtonsSettings.distanceBetweenButtons;
	}
}

void MenuButtonsManager::drawButtons(sf::RenderWindow& window)
{
	for (int i = 0; i < nbButtons; i++)
	{
		buttons.at(i).draw(window);
	}
}

void MenuButtonsManager::CheckButtonHover(MouseManager& mouse)
{
	for (int i = 0; i < nbButtons; i++)
	{
		if (buttons.at(i).getShape().getGlobalBounds().contains(mouse.getClickPosition()))
		{
			buttons.at(i).setTexture(&buttonsTextures[1 + i * 2]);
		}
		else
		{
			buttons.at(i).setTexture(&buttonsTextures[i * 2]);
		}
	}
}
