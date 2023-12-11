#include "PlayerHud.h"

PlayerHud::PlayerHud(sf::Font& font, bool isEnemy, std::string name, std::string kd, std::string score, sf::Texture& playerTexture)
{
	this->isEnemy = isEnemy;

	if (!isEnemy)
	{
		bgTexture.loadFromFile(playerHudSettings.hudPath);
		background = new EntityRectangle(playerHudSettings.hudSize, sf::Vector2f(0, 0), bgTexture);
	}
	else
	{
		background = nullptr;
	}

	nameTxt = new EntityText(font, playerHudSettings.namePos, playerHudSettings.nameSize, name, playerHudSettings.nameColor);
	kdTxt = new EntityText(font, playerHudSettings.kdPos, playerHudSettings.kdSize, "K/D: " + kd, playerHudSettings.kdColor);
	scoreTxt = new EntityText(font, playerHudSettings.scorePos, playerHudSettings.scoreSize, "Score: " + score, playerHudSettings.scoreColor);
	playerPicture = new EntityCircle(playerHudSettings.pictureSize, playerHudSettings.picturePos, playerTexture);

	if (isEnemy)
	{
		clock = new sf::Clock;
	}
	else
		istxtok = true;

}

void PlayerHud::draw(sf::RenderWindow& window)
{
	if(!isEnemy)
		background->draw(window);

	if(istxtok)
	{
		nameTxt->draw(window);
		kdTxt->draw(window);
		scoreTxt->draw(window);	
	}
	else if(clock != nullptr && clock->getElapsedTime().asMilliseconds() >= 300) {
		InitEnemyTxt();
	}

	playerPicture->draw(window);
}

void PlayerHud::InitEnemyTxt()
{
	WindowSettings w;
	playerPicture->setPosition(sf::Vector2f(w.gameWindowSize.x - playerHudSettings.picturePos.x - playerHudSettings.pictureSize * 2, playerHudSettings.picturePos.y));

	nameTxt->getText().setOrigin(sf::Vector2f(nameTxt->getText().getGlobalBounds().width, 0));
	nameTxt->SetPosition(sf::Vector2f(w.gameWindowSize.x - playerHudSettings.namePos.x - playerHudSettings.pictureSize * 2, playerHudSettings.namePos.y));

	kdTxt->getText().setOrigin(sf::Vector2f(kdTxt->getText().getGlobalBounds().width, 0));
	kdTxt->SetPosition(sf::Vector2f(w.gameWindowSize.x - playerHudSettings.kdPos.x - playerHudSettings.pictureSize * 2, playerHudSettings.kdPos.y));

	scoreTxt->getText().setOrigin(sf::Vector2f(scoreTxt->getText().getGlobalBounds().width, 0));
	scoreTxt->SetPosition(sf::Vector2f(w.gameWindowSize.x - playerHudSettings.scorePos.x - playerHudSettings.pictureSize * 2, playerHudSettings.scorePos.y));

	istxtok = true;
	clock = nullptr;
}


