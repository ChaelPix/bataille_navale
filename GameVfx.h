#pragma once

#include "AnimatedEntity.h"
#include "Settings.h"

class GameVfx
{

private:
	GameVFXSettings gameVfxSettings;
	GridSettings gridSettings;
	int gridSize;

	std::vector<Entity*> entities;
	std::vector<AnimatedEntity*> attacksAnimation;

	sf::Texture missTexture;
	std::vector<sf::Texture> attackTextures;
	std::vector<sf::Texture> enemyFireTextures;
	std::vector<sf::Texture> playerFireTextures;

	sf::Vector2f getGridPos(bool isEnnemy);
	sf::Vector2f getEntityPos(sf::Vector2f gridPos, int x, int y);

public:

	GameVfx();
	void CreateMissCell(int x, int y, bool isEnnemy);
	void CreateAttackCell(int x, int y, bool isEnnemy);
	void CreateFireCell(int x, int y, bool isEnnemy);
	void draw(sf::RenderWindow &window);



};

