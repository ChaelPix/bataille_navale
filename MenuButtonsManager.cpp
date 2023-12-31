#include "MenuButtonsManager.h"
#include <iostream>



MenuButtonsManager::MenuButtonsManager(sf::Font &font)
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

	matchmakingText = new EntityText(font, menuButtonsSettings.matchmakingTxtPos, menuButtonsSettings.matchmakingTxtFontSize, "Matchmaking");

	sf::Vector2f matchmakingButPos = sf::Vector2f(
		menuButtonsSettings.matchmakingTxtPos.x + 514/2 - (menuButtonsSettings.buttonsSize.x * 0.75f / 2),
		menuButtonsSettings.matchmakingTxtPos.y + 115 + menuButtonsSettings.distanceBetweenButtons );
	buttons.push_back(EntityRectangle(menuButtonsSettings.buttonsSize * 0.75f, matchmakingButPos));
	buttons.at(nbButtons).setTexture(&buttonsTextures[7]);

	nbPoints = 0;

	timer = new WaitTimer(menuButtonsSettings.matchmakingPointTimer);
}

void MenuButtonsManager::updateMatchmakingTxt()
{
	if (timer->update(true))
	{
		nbPoints = (nbPoints + 1) % 4;
		std::string t = "Matchmaking";
		for (int i = 0; i < nbPoints; i++)
			t += ".";
		matchmakingText->SetText(t);
	}
}

void MenuButtonsManager::draw(sf::RenderWindow& window)
{
	if (!isMatchMaking)
	{
		for (int i = 0; i < nbButtons; i++)
			buttons.at(i).draw(window);	
	}
	else
	{	
		updateMatchmakingTxt();
		matchmakingText->draw(window);
		buttons.at(nbButtons).draw(window);
	}
}

bool MenuButtonsManager::ButtonClickAction(int btnId)
{
	switch (btnId)
	{
	case 0:
		if (isMatchMaking)
			return false;

		isMatchMaking = true;
		break;
		
	case 2:

		return true;

	case 3:
		if (!isMatchMaking)
			return false;

		isMatchMaking = false;

		break;
	}

	return false;
}

int MenuButtonsManager::CheckButtonHover(MouseManager& mouse)
{
	int buttonClick = 0;

	for (int i = 0; i < nbButtons+1; i++)
	{
		if (buttons.at(i).getShape().getGlobalBounds().contains(mouse.getClickPosition()))
		{
			buttons.at(i).setTexture(&buttonsTextures[1 + i * 2]);

			if (mouse.isMouseClicked())
			{
				ButtonClickAction(i);
				buttonClick = i;
			}
		}
		else
		{
			buttons.at(i).setTexture(&buttonsTextures[i * 2]);
		}
	}

	return buttonClick;
}

bool MenuButtonsManager::getIsMatchMaking()
{
	return isMatchMaking;
}

void MenuButtonsManager::setIsMatchMaking(bool action)
{
	isMatchMaking = action;
}