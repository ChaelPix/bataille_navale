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
    objBDD = new BsBDD();
    FontSettings fontSettings;
    gameFont.loadFromFile(fontSettings.fontPath);
    hasLogged = false;
    areImagesOk = false;
    fxobj = new SfxManager();
    imageLoadingThread = std::thread(&GameApplication::LoadImages, this);
    checkForSaveFile();
}

void GameApplication::LoadImages() {
    BackgroundSettings bg;
    for (int i = 0; i < bg.nbMenuImgs; i++) {
        sf::Texture t;
        t.loadFromFile(bg.menupath + std::to_string(i + 1) + ".jpg");
        menuBg.push_back(t);
    }
    for (int i = 0; i < bg.nbGameImgs; i++) {
        sf::Texture t;
        t.loadFromFile(bg.gamepath + std::to_string(i + 1) + ".jpg");
        gameBg.push_back(t);
    }

    areImagesOk = true;

    LockerSettings lck;
    for (int i = 0; i < lck.nbImages; i++) {
        sf::Texture t;
        t.loadFromFile(lck.path[i]);
        charactersPictures.push_back(t);
    }
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
    case 'M':
        return MessageType::Chat;
    case 'F':
        return MessageType::End;
    case 'P':
        return MessageType::PlayerInfo;
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

bool GameApplication::getHasDataFile()
{
    return hasDataFile;
}

void GameApplication::checkForSaveFile()
{
    std::vector<std::string> dataVector;

    SaveData saver;

    dataVector = saver.loadDataFromFile();

    if (dataVector.at(0) == "")
    {
        hasDataFile = false;
        return;
    }

    objBDD->setIdPlayers(dataVector.at(0));
    objBDD->setMdp(dataVector.at(1));
    objBDD->setIdPicture(std::stoi(dataVector.at(2)));

    hasDataFile = true;
}

std::vector<sf::Texture>& GameApplication::getMenuBg()
{
    return menuBg;
}

std::vector<sf::Texture>& GameApplication::getGameBg()
{
    return gameBg;
}
std::vector<sf::Texture>& GameApplication::getCharactersImgs()
{
    return charactersPictures;
}

sf::Texture& GameApplication::getChoosenPicture()
{
    return charactersPictures.at(getBddObj().getIdPicture());
}

void GameApplication::ChangeState(State newState) {
    currentState = newState;

    sf::Vector2i windowPos = sf::Vector2i(0, 0);

    if (currentWindow)
    {
        windowPos = currentWindow->GetWindowPosition();
        currentWindow->Stop();
        currentWindow = nullptr;
        fxobj->clear();
    }

    switch (currentState) 
    {
        case State::Splash:
            currentWindow = new SplashWindow(*this, windowPos);
            break;

        case State::Menu:
            if (!hasLogged && imageLoadingThread.joinable())
                imageLoadingThread.join();
            currentWindow = new MenuWindow(*this, windowPos);
            currentWindow->wName = "menu";
            break;

        case State::Locker:
            if(!areImagesOk && imageLoadingThread.joinable())
                    imageLoadingThread.join();
            currentWindow = new LockerWindow(*this, windowPos);
            currentWindow->wName = "lck";
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
   try
   {
       this->client = new TCPClient(networkSettings.serverIp, networkSettings.serverPort);
       return true;
   }
   catch (const std::runtime_error& e)
   {
       return false;
   }

}
bool GameApplication::CreateClient(std::string ip)
{
    serverIP = ip;
    try
    {
        this->client = new TCPClient(ip, 12345);
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

