#include "Application.h"

GameApplication::GameApplication() : currentState(State::Menu) {
    ChangeState(currentState);
}

GameApplication::GameApplication(State state) : currentState(state) {
    ChangeState(currentState);
}

GameApplication::~GameApplication()
{
    client->closeSocket();
}

void GameApplication::Run() {
    while (running) {
        currentWindow->Run();
    }
}

void GameApplication::Close() {
    running = false;
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

