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
	kdTxt = new EntityText(font, playerHudSettings.kdPos, playerHudSettings.kdSize, kd, playerHudSettings.kdColor);
	scoreTxt = new EntityText(font, playerHudSettings.scorePos, playerHudSettings.scoreSize, score, playerHudSettings.scoreColor);
	playerPicture = new EntityCircle(playerHudSettings.pictureSize, playerHudSettings.picturePos, playerTexture);

}

void PlayerHud::draw(sf::RenderWindow& window)
{
	if(!isEnemy)
		background->draw(window);

	nameTxt->draw(window);
	kdTxt->draw(window);
	scoreTxt->draw(window);
	playerPicture->draw(window);
}
