#pragma once

#include "SfmlWindow.h"
#include "Application.h"

#include "Settings.h"
#include "AnimatedBackground.h"
#include "MouseManager.h"
#include "MenuButtonsManager.h"
#include "BsBDD.h"

class MenuWindow : public SfmlWindow
{
public:
    MenuWindow(GameApplication& application);
    ~MenuWindow();


protected:
    void Initialize() override;

    void HandleEvents(sf::Event& event) override;

    void StatSQL();

    void Update() override;

    void Render() override;

private:
    GameApplication* application;
    FontSettings font;
    BsBDD objBDD;
    sf::Text stat; 
    sf::Text name; 
    sf::Font FontStat;
    MouseManager mouseManager;
    AnimatedBackground* menuBackground;
    MenuButtonsManager* menuButtonsManager;
    std::string statInformation;
    std::string NameInformation;
    bool isLoad = false;
    std::vector<Entity*> entitiesPtr;
};

