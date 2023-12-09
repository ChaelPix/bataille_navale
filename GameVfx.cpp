#include "GameVfx.h"

GameVfx::GameVfx()
{
	missTexture.loadFromFile(gameVfxSettings.missImagePath);
}


void GameVfx::CreateMissCell(int x, int y, bool isEnnemy)
{
	sf::Vector2f pos;

	isEnnemy ? pos = gridSettings.ennemyGridPosition : pos = gridSettings.playerGridPosition;

	int gridSize = gridSettings.squareSize / gridSettings.nbPixels;

	entities.push_back(new EntityRectangle(sf::Vector2f(gridSize, gridSize), sf::Vector2f(pos.x + x * gridSize, pos.y + y * gridSize), missTexture));
}


void GameVfx::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < entities.size(); i++)
		entities.at(i)->draw(window);

}
