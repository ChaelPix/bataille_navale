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

    // loading music files
    BackgroundMusic.openFromFile(settings.pathBGM);
    GameMusic.openFromFile(settings.pathGME);
    LockerMusic.openFromFile(settings.pathLocker);

    // current music
    currentMusic = &BackgroundMusic;
}

void SfxManager::creatSfx(sfx type){
    sf::Sound sound;
        sound.setBuffer(sfxVector.at((static_cast<int>(type))));
        sfxs.push_back(sound);
}

void SfxManager::PlayMusic(bgm bgm)
{

}
