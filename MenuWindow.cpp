#include "MenuWindow.h"

MenuWindow::MenuWindow(GameApplication& application, const sf::Vector2i& windowPos)
    :
    SfmlWindow("Valiant", WindowSettings().menuWindowSize, windowPos),
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
    application->fxobj->PlayMusic(SfxManager::bgm::menu);
    application->fxobj->setMusicLoop(SfxManager::bgm::menu, true);

    if (application->getAreImagesOk())
    {
        menuBackground = new AnimatedEntity(70, true, false, windowSettings.menuWindowSize, sf::Vector2f(0, 0), application->getMenuBg());
        playerPicture = new EntityCircle(50, sf::Vector2f(windowSettings.menuWindowSize.x - 135, 5), application->getChoosenPicture());
    }
    else
    {
        menuBackground = new AnimatedEntity("ressources/UI/backgrounds/menuBg/menu_", 50, 70, true, false, windowSettings.menuWindowSize, sf::Vector2f(0, 0));
        playerPicture = new EntityCircle(50, sf::Vector2f(windowSettings.menuWindowSize.x - 135, 5));
    }    

    entitiesPtr.push_back(new EntityRectangle(sf::Vector2f(479, 749), sf::Vector2f(windowSettings.gameWindowSize.x - 720, 0), "ressources/UI/ui_menu_sideMenu.png"));
    menuButtonsManager = new MenuButtonsManager(application->getGameFont());

    LoginMenu::loginByFileInfo l;
    l.hasFile = application->getHasDataFile();
    l.id = application->getBddObj().getIdPlayers();
    l.mdp = application->getBddObj().getmdp();

    loginMenu = new LoginMenu(application->getGameFont(), application->getBddObj(), application->getHasLogged(), l);

    MenuServerInfoTextSettings ts;
    serverInfoTxt = new EntityText(application->getGameFont(), ts.textPosition, ts.characterSize, sf::Color::Red);

    

}

void MenuWindow::HandleEvents(sf::Event& event) {
    mouseManager.update(event, window);
}

void MenuWindow::Update(sf::Event& event) {
    menuState = loginMenu->update(event, mouseManager);

    
    CheckExitButton();
    HandleMatchmaking();
}

void MenuWindow::HandleMatchmaking()
{
    if (menuButtonsManager->getIsMatchMaking())
    {
        if (application->client == nullptr)
        {
            if (!application->CreateClient())
            {
                serverInfoTxt->SetText("Server is Inactive");
                menuButtonsManager->setIsMatchMaking(false);
                return;
            }
            else
            {
                serverInfoTxt->SetText("");
            }
        }

        std::string message = application->client->getMessage();
        if (message == "matchmaking")
        {
            std::cout << "Got Matchmaking from server ";
            application->client->sendMessage("OK");
            return;
        }

        if (application->isCorrectMessageType(message))
        {
            application->setClientStartFirst(message == "GStart");
            running = false;
            application->ChangeState(GameApplication::State::Game);
            application->fxobj->PlayMusic(SfxManager::bgm::game);
            application->fxobj->setMusicLoop(SfxManager::bgm::game, true);
        }

    }
    else if (application->client != nullptr) {
        application->DeleteClient();
    }
}

void MenuWindow::CheckExitButton()
{
    int id = menuButtonsManager->CheckButtonHover(mouseManager);
    if (id == 2)
    {
        running = false;
        application->Close();
    }
    else if (id == 1)
    {
        running = false;
        application->ChangeState(GameApplication::State::Locker);
        application->fxobj->PlayMusic(SfxManager::bgm::locker);
        application->fxobj->setMusicLoop(SfxManager::bgm::locker, true);
    }
}

void MenuWindow::Render()
{
    if (!running)
        return;

    menuBackground->draw(window);
    loginMenu->draw(window, menuState);

    if (menuState == LoginMenu::MenuState::OnMenu)
    {
        for (auto& entity : entitiesPtr)
            entity->draw(window);

        menuButtonsManager->draw(window);
        serverInfoTxt->draw(window);
        playerPicture->draw(window);

        if (playerInfosText.empty())
            InitPlayerInfo();
        else
            for (int i = 0; i < playerInfosText.size(); i++)
                playerInfosText.at(i)->draw(window);

    }
   
}

void MenuWindow::InitPlayerInfo()
{
    PlayerInfoSettings ps;

    std::string s[6];
    BsBDD& bdd = application->getBddObj();

    s[0] = "     " + bdd.getIdPlayers();
    s[1] = "Score: " + bdd.getScore();
    s[2] = "Games Played: " + bdd.getNbGames();
    s[3] = " Victories: " + bdd.getNbWonGames();
    s[4] = " Defeats: " + bdd.getNbLostGames();
    s[5] = "K/D: " + bdd.getRatio();

    for (int i = 0; i < 6; i++)
    {
        sf::Vector2f pos = sf::Vector2f(ps.textPosition.x + ps.textOffset.x * i, ps.textPosition.y + ps.textOffset.y * i);
        int characterSize = ps.characterSize;

        if (i == 0) 
            characterSize += 10;
        else
            pos.y += 10;
        playerInfosText.push_back(new EntityText(application->getGameFont(), pos, characterSize, s[i], ps.textColors[i]));
    }

   
}



