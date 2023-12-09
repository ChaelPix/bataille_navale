#include "EndPanel.h"

EndPanel::EndPanel()
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
}

void EndPanel::Show(bool isVictory)
{
	int id = 0;
	if (isVictory) id = 1;

	endImage->setTexture(&imagesTextures[id]);
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
}
