#pragma once

#include <memory>
#include "SfmlWindow.h"
#include "GameWindow.h"
#include "MenuWindow.h"
#include "TCPClient.h"


class GameApplication {

public:
    enum class State {
        Menu,
        Game
    };

    TCPClient* client;
private:
    bool running = true;
    State currentState;
    std::unique_ptr<SfmlWindow> currentWindow;

public:
    GameApplication();
    GameApplication(State state = State::Menu);
    ~GameApplication();

    void Run();

    void ChangeState(State newState);

    void CreateClient();

    void Close();
};
