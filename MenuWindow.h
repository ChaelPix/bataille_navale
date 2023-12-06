#pragma once

#include "SfmlWindow.h"
#include "Application.h"

#include "Settings.h"
#include "AnimatedBackground.h"
#include "MouseManager.h"
#include "MenuButtonsManager.h"
#include "BsBDD.h"
#include "LoginMenu.h"

class MenuWindow : public SfmlWindow
{
public:
    MenuWindow(GameApplication& application);
    ~MenuWindow();


protected:
    void Initialize() override;

    void HandleEvents(sf::Event& event) override;

    void Update(sf::Event& event) override;

    void Render() override;

private:
    GameApplication* application;
    BsBDD objBDD;

    MouseManager mouseManager;
    AnimatedBackground* menuBackground;
    MenuButtonsManager* menuButtonsManager;
    std::vector<Entity*> entitiesPtr;

    LoginMenu* loginMenu;
};

/*

    sf::Text stat;
    sf::Text name;
    sf::Font FontStat;
    
*/