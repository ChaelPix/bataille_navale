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
    if (buffer.loadFromFile(settings.pathVoicDefeat)) {
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

void SfxManager::clear()
{
    sfxs.clear();
}

void SfxManager::PlayMusic(bgm bgm)
{
    // Arrêter la musique actuelle si elle est en train de jouer
    if (currentMusic && currentMusic->getStatus() == sf::Music::Playing) {
        currentMusic->stop();
    }

    // Jouer la nouvelle musique en fonction du paramètre bgm
    switch (bgm) {
    case bgm::menu:
        currentMusic = &BackgroundMusic;
        break;
    case bgm::game:
        currentMusic = &GameMusic;
        break;
    case bgm::locker:
        currentMusic = &LockerMusic;
        break;
    default:
        // Gestion d'un cas non prévu
        currentMusic = nullptr;
        return;
    }

    // Jouer la musique sélectionnée
    if (currentMusic) {
        currentMusic->play();
    }
}


void SfxManager::setSfxVolume(float volume) {
    for (auto& sound : sfxs) {
        sound.setVolume(volume);
    }
}

void SfxManager::setMusicLoop(bgm bgmType, bool loop) {
    sf::Music* music = nullptr;
    switch (bgmType) {
    case bgm::menu:
        music = &BackgroundMusic;
        break;
    case bgm::game:
        music = &GameMusic;
        break;
    case bgm::locker:
        music = &LockerMusic;
        break;
    default:
        return;
    }

    if (music) {
        music->setLoop(loop);
    }
}