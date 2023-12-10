#pragma once

#include "SfmlWindow.h"
#include "Application.h"

#include "Settings.h"
#include "AnimatedEntity.h"
#include "MouseManager.h"
#include "MenuButtonsManager.h"
#include "EntityRectangle.h"
#include "BsBDD.h"
#include "LoginMenu.h"


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

    void debug();

    void Render() override;

private:
    GameApplication* application;
    LockerSettings LckSettings;
    MouseManager mouseManager;
    AnimatedEntity* menuBackground;
    MenuButtonsManager* menuButtonsManager;
    std::vector<EntityRectangle*> entitiesPtr;
    std::vector<sf::Texture*> PictureCases;
    std::map<std::string, bool> lockerSection;
    int l, p;
    sf::Texture buttonPrevTexture, buttonNextTexture;
    sf::Sprite buttonPrevSprite, buttonNextSprite;
    int currentSectionIndex = 0;
    sf::Vector2f buttonPosition;
};




