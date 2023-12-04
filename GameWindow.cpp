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
}

void GameWindow::HandleEvents(sf::Event& event) {
    mouseManager.update(event, window);
}

void GameWindow::Update() {
    playerBoatsManager.dragBoats(mouseManager);
}

void GameWindow::Render()
{
    waterBackground->draw(window);
    gridPlayer.DrawGrid(window);
    playerBoatsManager.draw(window);

    for (auto& entity : entitiesPtr)
        entity->draw(window);
    cloudManager->draw(window);
    gridEnemy.DrawGrid(window);

}
