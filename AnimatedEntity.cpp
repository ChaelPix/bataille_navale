#include "AnimatedEntity.h"

#include <iostream>

AnimatedEntity::AnimatedEntity(std::string name, int nbImgs, int timer, bool doLoop, bool doDie, sf::Vector2f windowSize) : EntityRectangle(windowSize)
{
	this->pathName = name;
	this->actualBgIndex = 0;
	this->timer = timer;
	this->doLoop = doLoop;
	this->doDie = doDie;

	this->tick = 0;
	this->step = 1;

	for (int i = 0; i < nbImgs; i++)
	{
        sf::Texture texture;
 
        std::string fileName = pathName + std::to_string(i + 1) + ".jpg";
		texture.loadFromFile(fileName);
		std::cout << "Loading : " << fileName << std::endl;
        this->bgImages.push_back(texture);
	}
}

void AnimatedEntity::draw(sf::RenderWindow& window)
{
	if (isDead)
		return;

	window.draw(shape);

	tick++;
	if (tick < timer)
		return;

	tick = 0;
	EntityRectangle::setTexture(&bgImages.at(actualBgIndex));

	actualBgIndex += step;

	if (actualBgIndex > 0 && actualBgIndex >= bgImages.size())
	{
		if (doDie)
		{
			isDead = true;
			return;
		}

		if (doLoop)
		{
			step = -1;
			actualBgIndex = bgImages.size() - 2;
		}else
			actualBgIndex = 0;
	}else if (actualBgIndex < 0)
	{
		step = 1;
		actualBgIndex = 1;
	}
}

bool AnimatedEntity::getIsDead()
{
	return this->isDead;
}

