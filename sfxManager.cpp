#include "SfxManager.h"

SfxManager::SfxManager() {
    // loading effect sonore
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(settings.pathClick)) {
        sfxVector.push_back(buffer);
    }
    if (buffer.loadFromFile(settings.pathExplosion)) {
        sfxVector.push_back(buffer);
    }
    if (buffer.loadFromFile(settings.pathsinkBoat)) {
        sfxVector.push_back(buffer);
    }
    if (buffer.loadFromFile(settings.pathVictory)) {
        sfxVector.push_back(buffer);
    }
    if (buffer.loadFromFile(settings.pathDefeat)) {
        sfxVector.push_back(buffer);
    }
    if (buffer.loadFromFile(settings.pathVoicVictory)) {
        sfxVector.push_back(buffer);
    }

    //// Initialisation of sf::Sound object with SoundBuffers
    //for (auto& buffer : sfxVector) {
    //    sf::Sound sound;
    //    sound.setBuffer(buffer);
    //    sfxs.push_back(sound);
    //}

        // Initialisation des objets sf::Sound avec les SoundBuffers
    sfxs.resize(sfxVector.size());
    for (size_t i = 0; i < sfxVector.size(); ++i) {
        sfxs[i].setBuffer(sfxVector[i]);
    }

    // loading music files
    BackgroundMusic.openFromFile(settings.pathBGM);
    GameMusic.openFromFile(settings.pathGME);
    LockerMusic.openFromFile(settings.pathLocker);

    // current music
    currentMusic = &BackgroundMusic;
}

void SfxManager::createSfx(sfx type) {
    sf::Sound sound;
    sfxs.push_back(sound);
    sfxs.at(sfxs.size() - 1).setBuffer(sfxVector.at((static_cast<int>(type))));
    sfxs.at(sfxs.size() - 1).play();
}

void SfxManager::update() {
    //for (int i = 0; i < sfxs.size(); i++)
    //{
    //    if(sfxs.at(i).getStatus() != sf::Sound::Playing)
    //}
    for (auto it = sfxs.begin(); it != sfxs.end(); ) {
        if (it->getStatus() != sf::Sound::Playing) {
            it = sfxs.erase(it); 
        }
        else {
            ++it;
        }
    }
}

void SfxManager::PlayMusic(bgm bgm)
{

}
