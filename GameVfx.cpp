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

	for (int i = 0; i < gameVfxSettings.nbEnemyFire; i++)
	{
		sf::Texture t;
		t.loadFromFile(gameVfxSettings.enemyFirePath + "b_" + std::to_string(i) + ".png");
		enemyFireBTextures.push_back(t);
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
	entitiesPos.push_back(sf::Vector2f(-10, -10));
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

	if (isEnnemy && lastBoatCell)
	{
		textures = &enemyFireBTextures;
		lastBoatCell = false;
	}

	entities.push_back(new AnimatedEntity(gameVfxSettings.fireTimer, true, false, sf::Vector2f(gridSize, gridSize), getEntityPos(pos, x, y), *textures));

	if(!isEnnemy)
		entitiesPos.push_back(sf::Vector2f(-10, -10));
	else
		entitiesPos.push_back(sf::Vector2f(x, y));

	CreateAttackCell(x, y, isEnnemy);
}

void GameVfx::isAdjacent(int x, int y, sf::Vector2f origin, std::set<std::pair<int, int>>& visited) {

	for (int i = 0; i < entitiesPos.size(); i++) {
		sf::Vector2f pos = entitiesPos.at(i);
		std::pair<int, int> posPair = { static_cast<int>(pos.x), static_cast<int>(pos.y) };

		if (pos != origin && visited.find(posPair) == visited.end() &&
			((pos.x == x && (pos.y == y - 1 || pos.y == y + 1)) ||
				(pos.y == y && (pos.x == x - 1 || pos.x == x + 1)))) {
			
			dynamic_cast<AnimatedEntity*>(entities.at(i))->ChangeTexturesRef(&enemyFireBTextures);

			visited.insert(posPair);
			isAdjacent(pos.x, pos.y, origin, visited);
		}
	}
}

void GameVfx::SinkBoatEffect(int x, int y) {
	std::set<std::pair<int, int>> visited;
	sf::Vector2f origin = sf::Vector2f(x, y);
	std::pair<int, int> originPair = { x, y };

	visited.insert(originPair);
	lastBoatCell = true;
	isAdjacent(x, y, origin, visited);
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

