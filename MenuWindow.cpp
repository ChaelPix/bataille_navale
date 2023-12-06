#include "MenuWindow.h"

MenuWindow::MenuWindow(GameApplication& application)
    :
    SfmlWindow("BattleShip", WindowSettings().menuWindowSize),
    application(&application)
{
    Initialize();
}

MenuWindow::~MenuWindow()
{
    running = false;
}

void MenuWindow::Initialize()
{
    menuBackground = new AnimatedBackground("ressources/UI/backgrounds/menuBg/menu_", 50, 28, true, windowSettings.menuWindowSize);
    entitiesPtr.push_back(new EntityRectangle(sf::Vector2f(523, 749), sf::Vector2f(windowSettings.gameWindowSize.x - 780, 0), "ressources/UI/ui_menu_sideMenu.png"));

}

void MenuWindow::HandleEvents(sf::Event& event) {
    mouseManager.update(event, window);
}

void MenuWindow::StatSQL() {

  

}

void MenuWindow::Update() {

    if (menuButtonsManager.CheckButtonHover(mouseManager))
    {
        running = false;
        application->Close();
    }

    if (menuButtonsManager.getIsMatchMaking())
    {
        if (application->client == nullptr)
            application->CreateClient();

        std::string message = application->client->getMessage();

        if (!message.empty() && message == "1" || message == "0") {
            running = false;
            application->ChangeState(GameApplication::State::Game);
        }
    }

    
}

void MenuWindow::Render()
{
    menuBackground->draw(window);
    for (auto& entity : entitiesPtr)
        entity->draw(window);

    menuButtonsManager.draw(window);

    objBDD.registerUser("snir", "snir");
    FontStat.loadFromFile(font.fontPath);

    // Cr�er un texte
    stat.setFont(FontStat);
    stat.setString(objBDD.getStatsInfo());
    stat.setCharacterSize(50); // en pixels
    stat.setFillColor(sf::Color::White);
    stat.setPosition(500, 500);
    window.draw(stat);

}