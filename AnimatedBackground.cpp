#include "AnimatedBackground.h"

#include <iostream>

AnimatedBackground::AnimatedBackground(std::string name, int nbImgs, int timer, bool doLoop, sf::Vector2f windowSize) : EntityRectangle(windowSize)
{
	this->pathName = name;
	this->actualBgIndex = 0;
	this->timer = timer;
	this->doLoop = doLoop;

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

void AnimatedBackground::draw(sf::RenderWindow& window)
{
	window.draw(shape);

	tick++;
	if (tick < timer)
		return;

	tick = 0;
	EntityRectangle::setTexture(&bgImages.at(actualBgIndex));

	actualBgIndex += step;

	if (actualBgIndex > 0 && actualBgIndex >= bgImages.size())
	{
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