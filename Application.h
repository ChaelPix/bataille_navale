#pragma once

#include <memory>
#include "SfmlWindow.h"
#include "GameWindow.h"
#include "MenuWindow.h"

class GameApplication {

public:
    enum class State {
        Menu,
        Game
    };

private:
    bool running = true;
    State currentState;
    std::unique_ptr<SfmlWindow> currentWindow;

public:
    GameApplication();
    GameApplication(State state);

    void Run();

    void ChangeState(State newState);


};
