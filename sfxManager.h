#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "settings.h"

class SfxManager{
public:
	enum class sfx { click, explosion, sinkBoat, victory, defeat,  voiceVictory, voiceDefeat, wrong };
	enum class bgm { menu, game, locker};

private:

	//Sfx
	
	std::vector<sf::SoundBuffer> sfxVector;
	std::vector<sf::Sound> sfxs;

	//Music
	sf::Music BackgroundMusic;
	sf::Music GameMusic;
	sf::Music LockerMusic;
	sf::Music* currentMusic;
	sfxSettings settings;

public:
	SfxManager();
	void createSfx(sfx type);
	void PlayMusic(bgm bgm);
	void clear();
	void setSfxVolume(float volume);
	void setMusicLoop(bgm bgmType, bool loop);
};

