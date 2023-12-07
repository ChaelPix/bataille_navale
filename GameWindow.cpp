#include "GameWindow.h"

GameWindow::GameWindow(GameApplication& application)
    : 
    SfmlWindow("BattleShip", WindowSettings().gameWindowSize),
    gridPlayer(gridSettings.nbPixels, gridSettings.squareSize, gridSettings.playerGridPosition, gridSettings.lineColor),
    gridEnemy(gridSettings.nbPixels, gridSettings.squareSize, gridSettings.ennemyGridPosition, gridSettings.lineColor),
    application(&application)
{
    Initialize();
}

void GameWindow::Initialize()
{
    waterBackground = new AnimatedBackground("ressources/UI/backgrounds/waterBg/water_", 59, 100, true, windowSettings.gameWindowSize);
    playerBoatsManager = new PlayerBoatsManager(&battleshipCore);

    timer.restart();
    gameState = GameState::Placing;
    cursor = new CursorCellSelector(battleshipCore, application->client);
}

void GameWindow::HandleEvents(sf::Event& event) {
    mouseManager.update(event, window);
}

<<<<<<< HEAD
//TEST HUD
void GameWindow::SetupHud(const std::string& imagePath, const std::string& fontPath, const std::string& text) {
    if (!hudTexture.loadFromFile(imagePath)) {
    }
    hudSprite.setTexture(hudTexture);

    if (!hudFont.loadFromFile(fontPath)) {
    }
    hudText.setFont(hudFont);
    hudText.setString(text);
    hudText.setCharacterSize(24); 
    hudText.setFillColor(sf::Color::White);

    hudSprite.setPosition(0, 0); 
    hudText.setPosition(10, 10);
}
void GameWindow::Hud() {
    //"ressources/UI/hud_Player.png"   "ressources/fonts/AGENCYB.TTF"  "Player 1"
    SetupHud("ressources/UI/hud_Player.png", "ressources/fonts/AGENCYB.TTF", "Player 1");
    window.draw(hudSprite);
    window.draw(hudText);
}

=======
>>>>>>> 4e712d68832275d89235d2463257b68ab3da298d
void GameWindow::Update(sf::Event &event) {
    
    //check Messages
    std::string message = "";
    message = application->client->getMessage();
    BattleshipCore::CellType attackCell;

    if (!message.empty())
    {
        switch (application->getMessageType(message))
        {
        case GameApplication::MessageType::BattleGrid:
            battleshipCore.setTargetGrid(message);
            break;
        case GameApplication::MessageType::Chat:
            std::cout << "Message : " << message;
            break;
        case GameApplication::MessageType::Game:
            std::cout << "Attack : " << message;
            attackCell = battleshipCore.deserializeAttack(message);
            std::cout << "Player Grid Attacked : \n" << battleshipCore.serializePlayerGrid(true).erase(0, 1) << std::endl;
            gameState = GameState::Attacking;
            break;
        }
    }
   
    CursorCellSelector::State attackState;
    //State Machine
    switch (gameState)
    {
    case GameState::Placing:

        playerBoatsManager->dragBoats(mouseManager);

        std::cout << timer.getElapsedTime().asSeconds() << std::endl;
        if (timer.getElapsedTime().asSeconds() >= 15) {
            timer.restart();
            playerBoatsManager->RandomPlacement();

            application->client->sendMessage(battleshipCore.serializePlayerGrid());
            gameState = GameState::WaitingGrid;
        }

        break;

    case GameState::WaitingGrid:

        if (battleshipCore.getHasReceivedOpponentGrid()) 
        {
            std::cout << "Opponent Grid Received : \n" << battleshipCore.serializePlayerGrid(false) << std::endl;
            application->getClientStartFirst() ? gameState = GameState::Attacking : gameState = GameState::Waiting;
        }

        break;

    case GameState::Attacking:
        attackState = cursor->update(mouseManager);

        switch (attackState)
        {
        case CursorCellSelector::State::Nothing:

            break;

        case CursorCellSelector::State::Attacked:
            gameState = GameState::Waiting;
            break;

        case CursorCellSelector::State::Win:
            std::cout << "WIN" << std::endl;
            break;

        case CursorCellSelector::State::ExtraTurn:

            break;

        default:

            break;
        }

        break;

    case GameState::Waiting:
        //std::cout << "you have to wait your turn !" << std::endl;
        break;
    }

}

void GameWindow::Render()
{
    waterBackground->draw(window);
    gridPlayer.DrawGrid(window);
    playerBoatsManager->draw(window);

    gridEnemy.DrawGrid(window);

    for (auto& entity : entitiesPtr)
        entity->draw(window);

    cloudManager->draw(window);
    gridEnemy.DrawGrid(window);

    if(gameState == GameState::Attacking)
         cursor->draw(window);

}
