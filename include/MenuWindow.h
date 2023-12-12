#pragma once

#include "SfmlWindow.h"
#include "Application.h"

#include "Settings.h"
#include "AnimatedEntity.h"
#include "EntityCircle.h"
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
    EntityText* serverInfoTxt;

    EntityCircle* playerPicture;

    LoginMenu* loginMenu;

    LoginMenu::MenuState menuState;

    std::vector<EntityText*> playerInfosText;
    void InitPlayerInfo();
};



    
