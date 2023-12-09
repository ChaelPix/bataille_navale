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
	sf::Texture attackTextures[4];

	sf::Vector2f getGridPos(bool isEnnemy);

public:

	GameVfx();
	void CreateMissCell(int x, int y, bool isEnnemy);
	void CreateAttackCell(int x, int y, bool isEnnemy);
	void draw(sf::RenderWindow &window);



};

