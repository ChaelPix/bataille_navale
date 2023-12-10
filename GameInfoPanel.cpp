#include "GameInfoPanel.h"
#include <filesystem>

GameInfoPanel::GameInfoPanel(sf::Font& font)
{
	backgroundTexture.loadFromFile(gameMenuSettings.timerbgPath);
	background = new EntityRectangle(gameMenuSettings.timerBgSize, gameMenuSettings.timerBgPos, backgroundTexture);

	timerTxt = new EntityText(font, gameMenuSettings.txtCenter, gameMenuSettings.timerTxtSize, "", gameMenuSettings.txtColor);
	turnTxt = new EntityText(font, gameMenuSettings.txtCenter, gameMenuSettings.nbTurnSize, "", gameMenuSettings.txtColor);
	infoTxt = new EntityText(font, gameMenuSettings.txtCenter, gameMenuSettings.gameInfoTxtSize, "", gameMenuSettings.txtColor);

	toDraw.push_back(background);
	toDraw.push_back(timerTxt);
	toDraw.push_back(turnTxt);
	toDraw.push_back(infoTxt);
}

void GameInfoPanel::updateTimer(float time, int max)
{
	float timeRemaining = max - time;
	int seconds = static_cast<int>(timeRemaining);
	int milliseconds = static_cast<int>((timeRemaining - seconds) * 1000);

	std::ostringstream timeStream;
	timeStream << std::setw(2) << std::setfill('0') << seconds << ":"
		<< std::setw(2) << std::setfill('0') << milliseconds;

	timerTxt->SetTextAndCenterX(timeStream.str());
	timerTxt->SetPosition(gameMenuSettings.txtCenter);
}

void GameInfoPanel::updateTurn(int turn)
{
	std::string s = "Turn " + std::to_string(turn);
	turnTxt->SetTextAndCenterX(s);
	turnTxt->SetPosition(gameMenuSettings.txtCenter + sf::Vector2f(0, 75));
}

void GameInfoPanel::updateGameInfo(std::string info)
{
	infoTxt->SetTextAndCenterX(info);
	infoTxt->SetPosition(gameMenuSettings.txtCenter + sf::Vector2f(0, 135));
}

void GameInfoPanel::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < toDraw.size(); i++)
		toDraw.at(i)->draw(window);
}