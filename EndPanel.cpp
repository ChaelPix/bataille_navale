#include "EndPanel.h"

EndPanel::EndPanel(sf::Font& font)
{
	for (int i = 0; i < 2; i++)
	{
		imagesTextures[i].loadFromFile(endMenuSettings.endImagesPath[i]);
		buttonTextures[i].loadFromFile(endMenuSettings.buttonImagePaths[i]);
	}

	endImage = new EntityRectangle(endMenuSettings.imageSize, endMenuSettings.imagePos);
	leaveButton = new EntityRectangle(endMenuSettings.buttonSize, endMenuSettings.buttonPos, buttonTextures[0]);
	panel = new EntityRectangle(endMenuSettings.panelSize, sf::Vector2f(0, 0), endMenuSettings.panelColor);
	doShow = false;

	scoreText = new EntityText(font, endMenuSettings.scorePos, endMenuSettings.scoreSize, "", sf::Color(225, 225, 0));
}

void EndPanel::Show(bool isVictory, int score, int wonPoints)
{
	int id = 0;
	if (isVictory) id = 1;

	endImage->setTexture(&imagesTextures[id]);
	scoreText->SetTextAndCenter("Score: " + std::to_string(score) + "\n" + "Points Won: " + std::to_string(wonPoints) + "\nNew Score: " + std::to_string(score + wonPoints));
	scoreText->SetPosition(endMenuSettings.scorePos);

	doShow = true;
}

bool EndPanel::isLeaveButtonClicked(MouseManager mouse)
{
	if (!doShow)
		return false;

	if (leaveButton->getShape().getGlobalBounds().contains(mouse.getClickPosition()))
	{
		leaveButton->setTexture(&buttonTextures[1]);
		return mouse.isMouseClicked();
	}
	else
	{
		leaveButton->setTexture(&buttonTextures[0]);
		return false;
	}

}

void EndPanel::draw(sf::RenderWindow& window)
{
	if (!doShow)
		return;

	panel->draw(window);
	endImage->draw(window);
	leaveButton->draw(window);
	scoreText->draw(window);
}
