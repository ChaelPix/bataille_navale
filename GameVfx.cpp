#include "GameVfx.h"

GameVfx::GameVfx()
{
	missTexture.loadFromFile(gameVfxSettings.missImagePath);

	for (int i = 0; i < 4; i++)
	{
		sf::Texture t;
		t.loadFromFile(gameVfxSettings.attacksPath + std::to_string(i) + ".png");
		attackTextures.push_back(t);
	}

	for (int i = 0; i < gameVfxSettings.nbEnemyFire; i++)
	{
		sf::Texture t; 
		t.loadFromFile(gameVfxSettings.enemyFirePath + std::to_string(i) + ".png");
		enemyFireTextures.push_back(t);
	}

	for (int i = 0; i < gameVfxSettings.nbPlayerFire; i++)
	{
		sf::Texture t; 
		t.loadFromFile(gameVfxSettings.playerFirePath + std::to_string(i) + ".png");
		playerFireTextures.push_back(t);
	}

	gridSize = gridSettings.squareSize / gridSettings.nbPixels;
}

sf::Vector2f GameVfx::getGridPos(bool isEnnemy)
{
	return isEnnemy ? gridSettings.ennemyGridPosition : gridSettings.playerGridPosition;;
}

sf::Vector2f GameVfx::getEntityPos(sf::Vector2f gridPos, int x, int y)
{
	return sf::Vector2f(gridPos.x + x * gridSize, gridPos.y + y * gridSize);
}


void GameVfx::CreateMissCell(int x, int y, bool isEnnemy)
{
	sf::Vector2f pos = getGridPos(isEnnemy);

	entities.push_back(new EntityRectangle(sf::Vector2f(gridSize, gridSize), getEntityPos(pos, x, y), missTexture));
	CreateAttackCell(x, y, isEnnemy);
}

void GameVfx::CreateAttackCell(int x, int y, bool isEnnemy)
{
	sf::Vector2f pos = getGridPos(isEnnemy);
	sf::Vector2f entityPos = getEntityPos(pos, x, y);
	entityPos.x = entityPos.x - (gameVfxSettings.attackTextureSize.x / 4);
	entityPos.y = entityPos.y - (gameVfxSettings.attackTextureSize.y / 4);
	attacksAnimation.push_back(new AnimatedEntity(gameVfxSettings.attacksTimer, false, true, gameVfxSettings.attackTextureSize, entityPos, attackTextures));
}

void GameVfx::CreateFireCell(int x, int y, bool isEnnemy)
{
	sf::Vector2f pos = getGridPos(isEnnemy);

	std::vector<sf::Texture>* textures;
	isEnnemy ? textures = &enemyFireTextures : textures = &playerFireTextures;

	entities.push_back(new AnimatedEntity(gameVfxSettings.fireTimer, true, false, sf::Vector2f(gridSize, gridSize), getEntityPos(pos, x, y), *textures));

	CreateAttackCell(x, y, isEnnemy);
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
