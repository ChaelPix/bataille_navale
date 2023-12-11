#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "SfmlWindow.h"

class sfxManager{

private:

	//Sfx
	enum class sfx { click, explosion,  sinkBoat, victory, defeat };
	std::vector<sf::SoundBuffer> sfxVector;

	//Music
	sf::Music BackgroundMusic;
	sf::Music GameMusic;
	sf::Music LockerMusic;

public:
	void creatSfx(sfx);

};

