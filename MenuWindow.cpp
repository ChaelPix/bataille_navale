#include "MenuWindow.h"

MenuWindow::MenuWindow(GameApplication& application)
    :
    SfmlWindow("BattleShip", WindowSettings().menuWindowSize),
    application(&application)
{
    Initialize();
}

void MenuWindow::Initialize()
{
    menuBackground = new AnimatedBackground("ressources/UI/backgrounds/menuBg/menu_", 100, 200, true, windowSettings.gameWindowSize);
}

void MenuWindow::HandleEvents(sf::Event& event) {
    mouseManager.update(event, window);
}

void MenuWindow::Update() {
    
}

void MenuWindow::Render()
{
    menuBackground->draw(window);

   /* for (auto& entity : entitiesPtr)
        entity->draw(window);*/
}