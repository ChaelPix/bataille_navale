#pragma once

#include "AnimatedEntity.h"
#include "Settings.h"

class GameVfx
{

private:
	std::vector<Entity*> entities;
	sf::Texture missTexture;

	GameVFXSettings gameVfxSettings;
	GridSettings gridSettings;


public:

	GameVfx();
	void CreateMissCell(int x, int y, bool isEnnemy);
	void draw(sf::RenderWindow &window);



};

