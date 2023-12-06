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
}

void GameWindow::HandleEvents(sf::Event& event) {
    mouseManager.update(event, window);
}

void GameWindow::Update() {
    
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

        std::string message = application->client->getMessage();
        std::cout << "Grille recue : \n" << message << std::endl;
        if (application->isCorrectMessageType()) 
        {
            gameState = GameState::Attacking;
        }

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

}
