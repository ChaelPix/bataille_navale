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
    menuBackground = new AnimatedBackground("ressources/UI/backgrounds/menuBg/menu_", 5, 175, true, windowSettings.gameWindowSize);

    entitiesPtr.push_back(new EntityRectangle(sf::Vector2f(523, 749), sf::Vector2f(windowSettings.gameWindowSize.x - 780, 0), "ressources/UI/ui_menu_sideMenu.png"));
}

void MenuWindow::HandleEvents(sf::Event& event) {
    mouseManager.update(event, window);
}

void MenuWindow::Update() {
    menuButtonsManager.CheckButtonHover(mouseManager);
}

void MenuWindow::Render()
{
    menuBackground->draw(window);

    for (auto& entity : entitiesPtr)
        entity->draw(window);

    menuButtonsManager.draw(window);
}