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
    client->closeSocket();
}

void GameApplication::Initialize()
{
    FontSettings fontSettings;
    gameFont.loadFromFile(fontSettings.fontPath);
}

void GameApplication::Run() {
    while (running) {
        currentWindow->Run();
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
    switch (currentState) 
    {
        case State::Splash:
            currentWindow.reset();
            currentWindow = std::make_unique<SplashWindow>(*this);
            break;

        case State::Menu:
            currentWindow.reset();
            currentWindow = std::make_unique<MenuWindow>(*this);
            break;

        case State::Game:
            currentWindow.reset();
            currentWindow = (std::make_unique<GameWindow>(*this));
            break;
    }
}

void GameApplication::CreateClient()
{
   this->client = new TCPClient("10.187.52.31", 12345);
}

