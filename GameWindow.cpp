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

//TEST HUD
void GameWindow::SetupHud(const std::string& imagePath, const std::string& fontPath, const std::string& text) {
    if (!hudTexture.loadFromFile(imagePath)) {
        // Gérer l'erreur de chargement de l'image
    }
    hudSprite.setTexture(hudTexture);

    if (!hudFont.loadFromFile(fontPath)) {
        // Gérer l'erreur de chargement de la police
    }
    hudText.setFont(hudFont);
    hudText.setString(text);
    hudText.setCharacterSize(24); // Taille du texte
    hudText.setFillColor(sf::Color::White); // Couleur du texte

    // Positionner l'image et le texte
    hudSprite.setPosition(0, 0); // Exemple de position
    hudText.setPosition(10, 10); // Ajustez selon vos besoins
}
void GameWindow::Hud() {
    //"ressources/UI/hud_Player.png"   "ressources/fonts/AGENCYB.TTF"  "Player 1"
    SetupHud("ressources/UI/hud_Player.png", "ressources/fonts/AGENCYB.TTF", "Player 1");
    window.draw(hudSprite);
    window.draw(hudText);
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
        case GameApplication::MessageType::Chat:
            std::cout << "Message : " << message;
        case GameApplication::MessageType::Game:
            std::cout << "Attack : " << message;
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
            std::cout << "Opponent Grid Received : \n" << message << std::endl;
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

    //TEST HUD
    Hud();

}
