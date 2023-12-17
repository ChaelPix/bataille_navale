#pragma once
#include "EntityRectangle.h"

class AnimatedEntity : public EntityRectangle
{
private :
	std::string pathName;
	std::vector<sf::Texture> bgImages;
	std::vector<sf::Texture>* refTextures;
	
	int actualBgIndex;
	int timer;
	bool doLoop;
	bool doDie;
	bool isDead;
	bool useRefTextures;
	int tick;
	int step;
	sf::Clock clock;

public :
	AnimatedEntity(std::string name, int nbImgs, int timer, bool doLoop, bool doDie, sf::Vector2f size, sf::Vector2f position);
	AnimatedEntity(int timer, bool doLoop, bool doDie, sf::Vector2f size, sf::Vector2f position, std::vector<sf::Texture>& textures);

	virtual void draw(sf::RenderWindow& window);
	void ChangeTexturesRef(std::vector<sf::Texture>* refTexts);

	bool getIsDead();
};

