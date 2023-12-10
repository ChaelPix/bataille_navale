#include "Application.h"

GameApplication::GameApplication() : currentState(State::Menu) {
    ChangeState(currentState);
    Initialize();
}

GameApplication::GameApplication(State state) : currentState(state) {
    ChangeState(currentState);
    Initialize();
}

GameApplication::~GameApplication()
{
    if(client != nullptr)
        client->closeSocket();
}

void GameApplication::Initialize()
{
    FontSettings fontSettings;
    gameFont.loadFromFile(fontSettings.fontPath);
    hasLogged = false;
    areImagesOk = false;
    BackgroundSettings bg;
    for (int i = 0; i < bg.nbMenuImgs; i++)
    {
        sf::Texture t;
        t.loadFromFile(bg.menupath + std::to_string(i+1) + ".jpg");
        menuBg.push_back(t);
    }
    for (int i = 0; i < bg.nbGameImgs; i++)
    {
        sf::Texture t;
        t.loadFromFile(bg.gamepath + std::to_string(i+1) + ".jpg");
        gameBg.push_back(t);
    }
    areImagesOk = true;
}

void GameApplication::Run() {

    while (running) 
    {
        if (currentWindow != nullptr) {
            currentWindow->Run();
        }
    }
}

void GameApplication::Close() {
    running = false;
}

void GameApplication::setClientStartFirst(bool isTrue)
{
    doClientStartFirst = isTrue;
}

bool GameApplication::getClientStartFirst()
{
    return doClientStartFirst;
}

BsBDD& GameApplication::getBddObj()
{
    objBDD = new BsBDD();
    return *objBDD;
}

bool GameApplication::isCorrectMessageType(std::string message, MessageType targetType)
{
    char firstLetter;
    targetType == MessageType::Game ? firstLetter = 'G' : firstLetter = 'C';

    return !message.empty() && message.at(0) == firstLetter;
}

GameApplication::MessageType GameApplication::getMessageType(std::string message)
{
    switch (message.at(0))
    {
    case 'G':
        return MessageType::Game;
    case 'B':
        return MessageType::BattleGrid;
    case 'C':
        return MessageType::Chat;
    case 'F':
        return MessageType::End;
    default :
        return MessageType::Unknown;
    }
}

sf::Font& GameApplication::getGameFont()
{  
    return gameFont;
}

bool& GameApplication::getHasLogged()
{
    return hasLogged;
}

void GameApplication::setHasLogged(bool action)
{
    hasLogged = action;
}

bool GameApplication::getAreImagesOk()
{
    return areImagesOk;
}

std::vector<sf::Texture>& GameApplication::getMenuBg()
{
    return menuBg;
}

std::vector<sf::Texture>& GameApplication::getGameBg()
{
    return gameBg;
}



void GameApplication::ChangeState(State newState) {
    currentState = newState;

    sf::Vector2i windowPos = sf::Vector2i(0, 0);

    if (currentWindow)
    {
        windowPos = currentWindow->GetWindowPosition();
        currentWindow->Stop();
        currentWindow = nullptr;
    }
        

    switch (currentState) 
    {
        case State::Splash:
            currentWindow = new SplashWindow(*this, windowPos);
            break;

        case State::Menu:
            currentWindow = new MenuWindow(*this, windowPos);
            currentWindow->wName = "menu";
            break;

        case State::Locker:
            currentWindow = new LockerWindow(*this, windowPos);
            currentWindow->wName = "menu";
            break;

        case State::Game:
            WindowSettings wSets;
            windowPos.x -= (wSets.gameWindowSize.x - wSets.menuWindowSize.x);
            windowPos.y -= (wSets.gameWindowSize.y - wSets.menuWindowSize.y);
            if (windowPos.x < 0) windowPos.x = 0;
            if (windowPos.y < 0) windowPos.y = 0;

            currentWindow = new GameWindow(*this, windowPos);
            currentWindow->wName = "game";
            break;
    }
}

bool GameApplication::CreateClient()
{
  // this->client = new TCPClient("10.187.52.31", 12345);
  
   try
   {
       this->client = new TCPClient("127.0.0.1", 12345);
       return true;
   }
   catch (const std::runtime_error& e)
   {
       return false;
   }

}

void GameApplication::DeleteClient()
{
    //client->sendMessage("SLEAVE");
    delete this->client;
    this->client = nullptr;
}

