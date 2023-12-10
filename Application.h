#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <thread>
#include "SfmlWindow.h"
#include "GameWindow.h"
#include "MenuWindow.h"
#include "SplashWindow.h"
#include "LockerWindow.h"
#include "TCPClient.h"
#include "BSBDD.h"


class GameApplication {

public:
    enum class State {
        Splash,
        Menu,
        Game,
        Locker,
    };

    enum class MessageType {
        Game,
        Chat,
        BattleGrid,
        End,
        Unknown
    };

    TCPClient* client;

private:
    bool running = true;
    State currentState;
    SfmlWindow* currentWindow;
    bool doClientStartFirst;
    BsBDD* objBDD;
    sf::Font gameFont;

    std::vector<sf::Texture> menuBg;
    std::vector<sf::Texture> gameBg;
    std::vector<sf::Texture> charactersPictures;

    bool hasLogged;
    bool areImagesOk;

    void Initialize();
    void LoadImages();

    std::thread imageLoadingThread;

public:
    GameApplication();
    GameApplication(State state = State::Menu);
    ~GameApplication();

    void Run();

    void ChangeState(State newState);

    bool CreateClient();
    void DeleteClient();

    void Close();

    void setClientStartFirst(bool isTrue);
    bool getClientStartFirst();

    BsBDD& getBddObj();

    bool isCorrectMessageType(std::string message = "", MessageType targetType = MessageType::Game);
    MessageType getMessageType(std::string message);

    sf::Font& getGameFont();

    bool& getHasLogged();
    void setHasLogged(bool action);
    bool getAreImagesOk();
    
    std::vector<sf::Texture>& getMenuBg();
    std::vector<sf::Texture>& getGameBg();
    std::vector<sf::Texture>& getCharactersImgs();
    sf::Texture& getChoosenPicture();

};
