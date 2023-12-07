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
    menuButtonsManager = new MenuButtonsManager(application->getGameFont());

    loginMenu = new LoginMenu(application->getGameFont());

    //objBDD.setPseudo("snir");
    //objBDD.displayPlayerInfo();
    //statInformation = objBDD.getStatsInfo();
    //NameInformation = objBDD.getIdPlayers();
    //std::cout << statInformation << ":::::::::::::::" << NameInformation;
}

void MenuWindow::HandleEvents(sf::Event& event) {
    mouseManager.update(event, window);
}

void MenuWindow::Update(sf::Event& event) {

    //loginMenu->update(event, mouseManager);

    if (menuButtonsManager->CheckButtonHover(mouseManager))
    {
        running = false;
        application->Close();
    }

    if (menuButtonsManager->getIsMatchMaking())
    {
        if (application->client == nullptr)
            application->CreateClient();

        std::string message = application->client->getMessage();
        if (application->isCorrectMessageType(message))
        {
            application->setClientStartFirst(message == "GStart");
            running = false;
            application->ChangeState(GameApplication::State::Game);
        }
    } 
}

void MenuWindow::Render()
{
    if (!running)
        return;

    menuBackground->draw(window);
    for (auto& entity : entitiesPtr)
        entity->draw(window);

    menuButtonsManager->draw(window);
    //loginMenu->draw(window);

}

/*
    if (!isLoad) {

        FontStat.loadFromFile(font.fontPath);

        // Créer un texte
        stat.setFont(FontStat);
        stat.setString(statInformation);
        stat.setCharacterSize(40); // en pixels
        stat.setFillColor(sf::Color(192, 192, 192));
        stat.setPosition(1023, 200);

        // Créer un texte
        name.setFont(FontStat);
        name.setString("Welcome " + NameInformation);
        name.setCharacterSize(65); // en pixels
        name.setFillColor(sf::Color(204, 102, 0));
        name.setPosition(950, 120);

        window.draw(stat);
        window.draw(name);
    }
*/