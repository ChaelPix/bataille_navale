#pragma once

#include "SfmlWindow.h"
#include "Application.h"

#include "Settings.h"
#include "AnimatedEntity.h"
#include "MouseManager.h"
#include "MenuButtonsManager.h"
#include "BsBDD.h"
#include "LoginMenu.h"

class MenuWindow : public SfmlWindow
{
public:
    MenuWindow(GameApplication& application, const sf::Vector2i& windowPos);
    ~MenuWindow();


protected:
    void Initialize() override;

    void HandleEvents(sf::Event& event) override;

    void Update(sf::Event& event) override;

    void HandleMatchmaking();
    void CheckExitButton();

    void Render() override;

private:
    GameApplication* application;

    MouseManager mouseManager;
    AnimatedEntity* menuBackground;
    MenuButtonsManager* menuButtonsManager;
    std::vector<Entity*> entitiesPtr;

    LoginMenu* loginMenu;

    sf::Text stat;
    sf::Text name;
    sf::Font FontStat;

    std::string statInformation;
    std::string NameInformation;

    LoginMenu::MenuState menuState;
};



    
