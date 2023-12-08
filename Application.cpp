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
    objBDD->connectToDB("10.187.52.4:3306", "batailleNavale", "batailleNavale");
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
    default :
        return MessageType::Unknown;
    }
}

sf::Font& GameApplication::getGameFont()
{  
    return gameFont;
}



void GameApplication::ChangeState(State newState) {
    currentState = newState;

    if (currentWindow)
    {
        currentWindow->Stop();
        currentWindow = nullptr;
    }
        

    switch (currentState) 
    {
        case State::Splash:
            currentWindow = new SplashWindow(*this);
            break;

        case State::Menu:
            currentWindow = new MenuWindow(*this);
            currentWindow->wName = "menu";
            break;

        case State::Game:
            currentWindow = new GameWindow(*this);
            currentWindow->wName = "game";
            break;
    }
}

void GameApplication::CreateClient()
{

  // this->client = new TCPClient("10.187.52.31", 12345);
   this->client = new TCPClient("127.0.0.1", 12345);

}

