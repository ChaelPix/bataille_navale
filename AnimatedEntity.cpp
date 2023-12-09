#include "AnimatedEntity.h"

#include <iostream>

AnimatedEntity::AnimatedEntity(std::string name, int nbImgs, int timer, bool doLoop, bool doDie, sf::Vector2f size, sf::Vector2f position) : EntityRectangle(size, position), refTextures(nullptr)
{
	this->pathName = name;
	this->actualBgIndex = 0;
	this->timer = timer;
	this->doLoop = doLoop;
	this->doDie = doDie;

	this->tick = 0;
	this->step = 1;

	useRefTextures = false;

	for (int i = 0; i < nbImgs; i++)
	{
        sf::Texture texture;
 
        std::string fileName = pathName + std::to_string(i + 1) + ".jpg";
		texture.loadFromFile(fileName);
		std::cout << "Loading : " << fileName << std::endl;
        this->bgImages.push_back(texture);
	}
}

AnimatedEntity::AnimatedEntity(int timer, bool doLoop, bool doDie, sf::Vector2f size, sf::Vector2f position, std::vector<sf::Texture>& textures) : EntityRectangle(size, position), refTextures(&textures)
{
	this->actualBgIndex = 0;
	this->timer = timer;
	this->doLoop = doLoop;
	this->doDie = doDie;
	this->tick = 0;
	this->step = 1;

	useRefTextures = true;
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

	std::vector<sf::Texture>* images = nullptr;
	useRefTextures ? images = &bgImages : images = refTextures;

	EntityRectangle::setTexture(&images->at(actualBgIndex));

	actualBgIndex += step;

	if (actualBgIndex > 0 && actualBgIndex >= images->size())
	{
		if (doDie)
		{
			isDead = true;
			return;
		}

		if (doLoop)
		{
			step = -1;
			actualBgIndex = images->size() - 2;
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

