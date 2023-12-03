#include "Application.h"

GameApplication::GameApplication() : currentState(State::Menu) {
    ChangeState(currentState);
}

GameApplication::GameApplication(State state) : currentState(state) {
    ChangeState(currentState);
}

void GameApplication::Run() {
    while (running && currentWindow) {
        currentWindow->Run();
    }
}

void GameApplication::ChangeState(State newState) {
    currentState = newState;
    switch (currentState) 
    {
    case State::Menu:
        currentWindow = std::make_unique<MenuWindow>(*this);
        break;
    case State::Game:
        currentWindow = std::move(std::make_unique<GameWindow>(*this));
        break;
    }
}

