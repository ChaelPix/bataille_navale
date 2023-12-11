#pragma once

#include "SfmlWindow.h"
#include "Application.h"
#include <SFML/Audio.hpp>

#include "Settings.h"
#include "AnimatedEntity.h"
#include "MouseManager.h"
#include "MenuButtonsManager.h"
#include "EntityRectangle.h"
#include "BsBDD.h"
#include "LoginMenu.h"
#include "EntityText.h"
#include "EntityTextBox.h"
#include "SfxManager.h"


class LockerWindow : public SfmlWindow
{
public:
    LockerWindow(GameApplication& application, const sf::Vector2i& windowPos);
    ~LockerWindow();

protected:
    void Initialize() override;

    void HandleEvents(sf::Event& event) override;

    void UpdateSectionState();

    void LockerManagement();

    void Update(sf::Event& event) override;

    void UpdatePos(sf::Time deltaTime);

    void debug();

    void Render() override;

private:
    GameApplication* application;
    LockerSettings LckSettings;
    FontSettings Fontonj;
    MouseManager mouseManager;
    MenuButtonsManager* menuButtonsManager;
    std::vector<EntityRectangle*> entitiesPtr;
    EntityRectangle* Background;
    EntityRectangle* valide;
    WindowSettings ws;
    BsBDD* bdd;
    SaveData obj;
    sf::Texture BackgroundTexture;
    sf::Texture valideTexture;
    std::vector<EntityText*> textInfo;
    std::vector<sf::Texture*> PictureCases;
    std::map<std::string, bool> lockerSection;
    std::vector<sf::Texture>* charactersImgs;

    int l, p, s;
    int section_starts[9] = { 0, 5, 9, 12, 19, 23, 29, 32, 40 };

    //bouton
    sf::Texture buttonPrevTexture, buttonNextTexture, exitButtonTexture;
    sf::Sprite buttonPrevSprite, buttonNextSprite, exitButtonSprite;
    int currentSectionIndex = -1;
    sf::Vector2f buttonPosition;

    //Music
    sf::Music music;

    //movement
    sf::Vector2f initialPosition; // Stores the initial position of the background
    float swaySpeed;              // How fast the background moves back and forth
    float swayMagnitude;          // The range of the sway movement
    sf::Clock clock;

    int pictureChoose;

    sf::Vector2f validPos;
    bool imageSelected = false;
};




