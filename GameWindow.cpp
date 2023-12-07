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
    cursor = new CursorCellSelector(battleshipCore);
}

void GameWindow::HandleEvents(sf::Event& event) {
    mouseManager.update(event, window);
}

void GameWindow::Update(sf::Event &event) {
    
    //check Messages
    std::string message = "";
    message = application->client->getMessage();

    if (!message.empty())
    {
        switch (application->getMessageType(message))
        {
        case GameApplication::MessageType::BattleGrid:
            battleshipCore.setTargetGrid(message);
            break;
        }
    }
   
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
            std::cout << "Opponent Grid Received : \n" << message << std::endl;
            application->getClientStartFirst() ? gameState = GameState::Attacking : gameState = GameState::Waiting;
        }

        break;

    case GameState::Attacking:
        std::cout << " you attack first !" << std::endl;
        break;

    case GameState::Waiting:
        std::cout << "you have to wait your turn !" << std::endl;
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

    std::cout << "cursor call : " << std::endl;
    cursor->draw(window, mouseManager);

}
