#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class SfxManager{

private:

	//Sfx
	enum class sfx { click, explosion,  sinkBoat, victory, defeat };
	std::vector<sf::SoundBuffer> sfxVector;
	std::vector<sf::Sound> sfxs;

	//Music
	enum class bgm { menu };
	sf::Music BackgroundMusic;
	sf::Music GameMusic;
	sf::Music LockerMusic;
	sf::Music* currentMusic;

public:

	SfxManager();
	void creatSfx(sfx type);
	void PlayMusic(bgm bgm);
};

