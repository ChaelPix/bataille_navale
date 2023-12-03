#include "MenuButtonsManager.h"

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
		buttons.push_back(new EntityRectangle(menuButtonsSettings.buttonsSize, startPos, buttonsTextures[i * 2]));
		startPos.y += menuButtonsSettings.buttonsSize.y + menuButtonsSettings.distanceBetweenButtons;
	}
}

void MenuButtonsManager::drawButtons(sf::RenderWindow& window)
{
	for (auto& entity : buttons)
		entity->draw(window);
}

void MenuButtonsManager::CheckButtonHover(const MouseManager& mouse)
{
	for (int i = 0; i < nbButtons; i++)
	{

	}
}
