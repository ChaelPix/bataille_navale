#pragma once
#include "EntityRectangle.h"

class AnimatedEntity : public EntityRectangle
{
private :
	std::string pathName;
	std::vector<sf::Texture> bgImages;
	int actualBgIndex;
	int timer;
	bool doLoop;

	int tick;
	int step;
	sf::Clock clock;

public :
	AnimatedEntity(std::string name, int nbImgs, int timer, bool doLoop, sf::Vector2f windowsSize);

	virtual void draw(sf::RenderWindow& window);
};

