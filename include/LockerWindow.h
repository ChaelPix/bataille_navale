#pragma once

#include "SfmlWindow.h"
#include "Application.h"
#include <SFML/Audio.hpp>
#include <cmath>
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
    std::vector<EntityText*> textInfoShop;
    EntityText* scoreText;
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

    std::vector<int> imageNumbers = { 
           35000, 5000, 4000, 3000, 500,//section 1
            25000, 20000, 1000, 2000,//section 2
             1000, 1500, 1500,//section 3
              1500, 1300, 2000, 1500, 1300, 500, 200,//section 4
               15000, 20000, 12000, 3000,//section 5
                5000, 30000, 15000, 50000, 30000, 20000,//section 6
                 5000, 15000, 15000,//section 7
                  0, 0, 0, 0, 0, 0, 0, 0,//section 8
                   100000, 120000, 130000, 120000, 200000, 180000, 80000, 300000,//section 9
    };
    float phaseOffset;
    float maxRotationAngle = 0.2f;
};




