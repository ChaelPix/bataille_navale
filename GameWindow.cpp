#include "GameWindow.h"

GameWindow::GameWindow(GameApplication& application, const sf::Vector2i& windowPos)
    : 
    SfmlWindow("BattleShip", WindowSettings().gameWindowSize, windowPos),
    gridPlayer(gridSettings.nbPixels, gridSettings.squareSize, gridSettings.playerGridPosition, gridSettings.lineColor),
    gridEnemy(gridSettings.nbPixels, gridSettings.squareSize, gridSettings.ennemyGridPosition, gridSettings.lineColor),
    application(&application)
{
    Initialize();
}

void GameWindow::Initialize()
{
    waterBackground = new AnimatedEntity("ressources/UI/backgrounds/waterBg/water_", 59, 100, true, false, windowSettings.gameWindowSize, sf::Vector2f(0, 0));
    playerBoatsManager = new PlayerBoatsManager(&battleshipCore);

    timer.restart();
    gameState = GameState::Placing;
    cursor = new CursorCellSelector(battleshipCore, application->client);
    endPanel = new EndPanel();
    gameVfx = new GameVfx();
}

void GameWindow::HandleEvents(sf::Event& event) {
    mouseManager.update(event, window);
}

void GameWindow::Update(sf::Event& event) {
    processMessages();
    handleGameState();
}

void GameWindow::processMessages() {
    std::string message = application->client->getMessage();

    if (!message.empty()) {
        switch (application->getMessageType(message)) {
                /*----------Receive Grid----------*/
            case GameApplication::MessageType::BattleGrid:
                battleshipCore.setTargetGrid(message);
                break;

                /*----------Receive Chat Message----------*/
            case GameApplication::MessageType::Chat:
                std::cout << "Message : " << message;
                break;

                /*----------Enemy Disconnected----------*/
            case GameApplication::MessageType::End:
                if (gameState != GameState::End)
                    endPanel->Show(true);
                gameState = GameState::End;
                break;

                /*----------Enemy Attack----------*/
            case GameApplication::MessageType::Game:
                std::cout << "Attack : " << message;
                BattleshipCore::AttackInfo attckPos = battleshipCore.deserializeAttack(message);
                BattleshipCore::CellType attackCell = battleshipCore.Attack(attckPos.y, attckPos.x, false);

                //if loose
                if (battleshipCore.areAllPlayerBoatsDown()) {
                    gameState = GameState::End;
                    endPanel->Show(false);
                }

                //if oponent hits
                if (attackCell != BattleshipCore::CellType::hit)
                    gameState = GameState::Attacking;
                else
                    gameVfx->CreateFireCell(attckPos.x, attckPos.y, false);

                //if he missed
                if (attackCell == BattleshipCore::CellType::water)
                    gameVfx->CreateMissCell(attckPos.x, attckPos.y, false);

                break;
            }
    }
}

void GameWindow::handleGameState() {
    CursorCellSelector::State attackState;
    sf::Vector2f MousePos;

    switch (gameState) {
            /*----------Placing----------*/
        case GameState::Placing:
            playerBoatsManager->dragBoats(mouseManager);
            if (timer.getElapsedTime().asSeconds() >= 15) {
                timer.restart();
                playerBoatsManager->RandomPlacement();
                application->client->sendMessage(battleshipCore.serializePlayerGrid());
                gameState = GameState::WaitingGrid;
            }
            break;
            /*----------WaitingGRID----------*/
    case GameState::WaitingGrid:
            if (battleshipCore.getHasReceivedOpponentGrid()) {
                std::cout << "Opponent Grid Received : \n" << battleshipCore.serializePlayerGrid(false) << std::endl;
                gameState = application->getClientStartFirst() ? GameState::Attacking : GameState::Waiting;
            }
            break;

            /*----------Attacking----------*/
    case GameState::Attacking:
        attackState = cursor->update(mouseManager);
        MousePos = cursor->getMouseGridPos(mouseManager);

        switch (attackState) {
            case CursorCellSelector::State::Nothing:
                break;

            case CursorCellSelector::State::Attacked:
                gameVfx->CreateMissCell(MousePos.x, MousePos.y, true);
                gameState = GameState::Waiting;
                break;

            case CursorCellSelector::State::Win:
                gameVfx->CreateFireCell(MousePos.x, MousePos.y, true);
                std::cout << "WIN" << std::endl;
                endPanel->Show(true);
                gameState = GameState::End;
                break;

            case CursorCellSelector::State::ExtraTurn:
                std::cout << "Extra turn !" << std::endl;
                gameVfx->CreateFireCell(MousePos.x, MousePos.y, true);
                gameState = GameState::Attacking;
                break;

            default:
                break;
            }
        break;

        /*----------WaitingAttack----------*/
    case GameState::Waiting:
       
        break;

        /*----------END----------*/
    case GameState::End:
        if (endPanel->isLeaveButtonClicked(mouseManager)) {
            std::cout << "LEAVE" << std::endl;
            application->DeleteClient();
            application->ChangeState(GameApplication::State::Menu);
        }
        break;
    }
}

void GameWindow::Render()
{
    bool isMouseOnEnemyGrid = gridEnemy.isMouseOnGrid(mouseManager);

    waterBackground->draw(window);
    gridPlayer.DrawGrid(window);
    playerBoatsManager->draw(window);

    gridEnemy.DrawGrid(window);

    for (auto& entity : entitiesPtr)
        entity->draw(window);

    gameVfx->draw(window);

    if(!isMouseOnEnemyGrid)
        gridEnemy.DrawGrid(window);

    cloudManager->draw(window);
   
    if (isMouseOnEnemyGrid)
        gridEnemy.DrawGrid(window);

    if(gameState == GameState::Attacking)
         cursor->draw(window);

    endPanel->draw(window);
}
