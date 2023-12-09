#include "GameVfx.h"

GameVfx::GameVfx()
{
	missTexture.loadFromFile(gameVfxSettings.missImagePath);

	for (int i = 0; i < 4; i++)
	{

	}

	gridSize = gridSettings.squareSize / gridSettings.nbPixels;
}

sf::Vector2f GameVfx::getGridPos(bool isEnnemy)
{
	return isEnnemy ? gridSettings.ennemyGridPosition : gridSettings.playerGridPosition;;
}


void GameVfx::CreateMissCell(int x, int y, bool isEnnemy)
{
	sf::Vector2f pos = getGridPos(isEnnemy);

	entities.push_back(new EntityRectangle(sf::Vector2f(gridSize, gridSize), sf::Vector2f(pos.x + x * gridSize, pos.y + y * gridSize), missTexture));
}

void GameVfx::CreateAttackCell(int x, int y, bool isEnnemy)
{
	sf::Vector2f pos = getGridPos(isEnnemy);

	//attacksAnimation.push_back(new AnimatedEntity()
}


void GameVfx::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < entities.size(); i++)
		entities.at(i)->draw(window);


	for (auto it = attacksAnimation.begin(); it != attacksAnimation.end();) 
	{
		if ((*it)->getIsDead()) {
			delete* it;
			it = attacksAnimation.erase(it); 
		}
		else {
			(*it)->draw(window);
			++it; 
		}
	}
}
