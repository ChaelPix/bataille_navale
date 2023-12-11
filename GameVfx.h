#pragma once

#include "AnimatedEntity.h"
#include "Settings.h"
#include <set>
#include <utility> 

class GameVfx
{

private:
	GameVFXSettings gameVfxSettings;
	GridSettings gridSettings;
	int gridSize;

	std::vector<Entity*> entities;
	std::vector<AnimatedEntity*> attacksAnimation;
	std::vector<sf::Vector2f> entitiesPos;

	sf::Texture missTexture;
	std::vector<sf::Texture> attackTextures;
	std::vector<sf::Texture> enemyFireTextures;
	std::vector<sf::Texture> enemyFireBTextures;
	std::vector<sf::Texture> playerFireTextures;
	std::vector<sf::Texture> missTextures;

	sf::Vector2f getGridPos(bool isEnnemy);
	sf::Vector2f getEntityPos(sf::Vector2f gridPos, int x, int y);

	bool lastBoatCell;
public:

	GameVfx();
	void CreateMissCell(int x, int y, bool isEnnemy);
	void CreateMissAttackCell(int x, int y, bool isEnnemy);
	void CreateAttackCell(int x, int y, bool isEnnemy);
	void CreateFireCell(int x, int y, bool isEnnemy);
	void draw(sf::RenderWindow &window);

	void SinkBoatEffect(int x, int y);
	void isAdjacent(int x, int y, sf::Vector2f origin, std::set<std::pair<int, int>>& visited);
};

