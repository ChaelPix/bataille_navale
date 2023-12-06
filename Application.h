#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "SfmlWindow.h"
#include "GameWindow.h"
#include "MenuWindow.h"
#include "SplashWindow.h"
#include "TCPClient.h"


class GameApplication {

public:
    enum class State {
        Splash,
        Menu,
        Game,
    };

    enum class MessageType {
        Game,
        Chat,
        BattleGrid,
        Unknown
    };

    TCPClient* client;

private:
    bool running = true;
    State currentState;
    std::unique_ptr<SfmlWindow> currentWindow;
    bool doClientStartFirst;

    sf::Font gameFont;

    void Initialize();

public:
    GameApplication();
    GameApplication(State state = State::Menu);
    ~GameApplication();

    void Run();

    void ChangeState(State newState);

    void CreateClient();

    void Close();

    void setClientStartFirst(bool isTrue);
    bool getClientStartFirst();

    bool isCorrectMessageType(std::string message = "", MessageType targetType = MessageType::Game);
    MessageType getMessageType(std::string message);

    sf::Font& getGameFont();
};
