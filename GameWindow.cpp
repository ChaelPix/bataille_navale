#include "GameWindow.h"

GameWindow::GameWindow(GameApplication& application, const sf::Vector2i& windowPos)
    : 
    SfmlWindow("Valiant", WindowSettings().gameWindowSize, windowPos),
    gridPlayer(gridSettings.nbPixels, gridSettings.squareSize, gridSettings.playerGridPosition, gridSettings.lineColor),
    gridEnemy(gridSettings.nbPixels, gridSettings.squareSize, gridSettings.ennemyGridPosition, gridSettings.lineColor),
    application(&application)
{
    Initialize();
}

void GameWindow::Initialize()
{
    waterBackground = new AnimatedEntity(100, true, false, windowSettings.gameWindowSize, sf::Vector2f(0, 0), application->getGameBg());
    playerBoatsManager = new PlayerBoatsManager(&battleshipCore);

    timer.restart();
    gameState = GameState::Placing;
    endPanel = new EndPanel(application->getGameFont());
    gameVfx = new GameVfx();
    cursor = new CursorCellSelector(battleshipCore, application->client, gameVfx);
    gameInfoPanel = new GameInfoPanel(application->getGameFont());
    gameInfoPanel->updateGameInfo("Place your Boats!");

    std::string playerInfo = "P" + application->getBddObj().getIdPlayers() + "$" + application->getBddObj().getRatio() + "$" + application->getBddObj().getScore() + "$" + std::to_string(application->getBddObj().getIdPicture());
    application->client->sendMessage(playerInfo);
}

void GameWindow::HandleEvents(sf::Event& event) {
    mouseManager.update(event, window);
}

void GameWindow::Update(sf::Event& event) {
    if (gameChat != nullptr)
        gameChat->Update(event);

    processMessages();
    handleGameState();
}

void GameWindow::processMessages() {
    std::string message = application->client->getMessage();

    if (!message.empty()) {
        switch (application->getMessageType(message)) {
                /*----------Receive Enemy Info----------*/
            case GameApplication::MessageType::PlayerInfo:
                std::cout << "Player Info : " << message;
                CreateHud(message);
                break;

                /*----------Receive Grid----------*/
            case GameApplication::MessageType::BattleGrid:
                battleshipCore.setTargetGrid(message);
                break;

                /*----------Receive Chat Message----------*/
            case GameApplication::MessageType::Chat:
                std::cout << "got message : " << message << std::endl;
                gameChat->ReceiveMessage(message);
                break;

                /*----------Enemy Disconnected----------*/
            case GameApplication::MessageType::End:
                if (gameState != GameState::End)
                    OnEnd(true);
                gameState = GameState::End;
                break;

                /*----------Enemy Attack----------*/
            case GameApplication::MessageType::Game:
                gameInfoPanel->updateTurn(++nbTurn);
                timer.restart();
                std::cout << "Attack : " << message;
                BattleshipCore::AttackInfo attckPos = battleshipCore.deserializeAttack(message);
                BattleshipCore::CellType attackCell = battleshipCore.Attack(attckPos.y, attckPos.x, false);

                //if loose
                if (battleshipCore.areAllPlayerBoatsDown()) {
                    gameState = GameState::End;                
                    OnEnd(false);
                }

                //if oponent no hits
                if (attackCell != BattleshipCore::CellType::hit)
                {
                    gameInfoPanel->updateGameInfo("Your Turn");
                    gameState = GameState::Attacking;
                    application->fxobj->createSfx(SfxManager::sfx::water);
                }
                else {
                    gameVfx->CreateFireCell(attckPos.x, attckPos.y, false);
                    application->fxobj->createSfx(SfxManager::sfx::explosion);
                    if (battleshipCore.CheckIfBoatDown(attckPos.y, attckPos.x, false, false, -1, -1))
                        application->fxobj->createSfx(SfxManager::sfx::sinkBoat);

                }

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
    float time = timer.getElapsedTime().asSeconds();
    if(gameState != GameState::End)
        gameInfoPanel->updateTimer(time, gameState == GameState::Placing ? gameSettings.timeToPlaceBoat : gameSettings.timeToPlay);

    switch (gameState) {
            /*----------Placing----------*/
        case GameState::Placing:
            playerBoatsManager->dragBoats(mouseManager); 
            if (time >= gameSettings.timeToPlaceBoat) {
                timer.restart();
                playerBoatsManager->RandomPlacement();
                gameState = GameState::SynchroGrid;
            }
            break;
        case GameState::SynchroGrid:
            if (time >= gameSettings.timeToSync) {
                timer.restart();
                application->client->sendMessage(battleshipCore.serializePlayerGrid());
                gameState = GameState::WaitingGrid;
            }
            break;
            /*----------WaitingGRID----------*/
    case GameState::WaitingGrid:
            if (battleshipCore.getHasReceivedOpponentGrid()) {
                std::cout << "Opponent Grid Received : \n" << battleshipCore.serializePlayerGrid(false) << std::endl;
                if (application->getClientStartFirst())
                {
                    gameState = GameState::Attacking;
                    gameInfoPanel->updateGameInfo("Your Turn");
                }
                else
                {
                    gameState = GameState::Waiting;
                    gameInfoPanel->updateGameInfo("Enemy Turn");
                }
       
                gameInfoPanel->updateTurn(nbTurn);
                timer.restart();
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
               
                gameInfoPanel->updateTurn(++nbTurn);
                gameInfoPanel->updateGameInfo("Enemy Turn");
                application->fxobj->createSfx(SfxManager::sfx::water);

                gameState = GameState::Waiting;
                timer.restart();
                break;

            case CursorCellSelector::State::Win:
                gameVfx->CreateFireCell(MousePos.x, MousePos.y, true);
                std::cout << "WIN" << std::endl;
                OnEnd(true);
                gameState = GameState::End;
                application->fxobj->createSfx(SfxManager::sfx::explosion);
                break;

            case CursorCellSelector::State::ExtraTurn:
                gameVfx->CreateFireCell(MousePos.x, MousePos.y, true);
                application->fxobj->createSfx(SfxManager::sfx::explosion);
                gameInfoPanel->updateTurn(++nbTurn);
                gameState = GameState::Attacking;

                timer.restart();
                break;

            default:
                break;
            }

        if (time >= gameSettings.timeToPlay) {
            gameInfoPanel->updateGameInfo("Enemy Turn");
            timer.restart();
            gameState = GameState::Waiting;
            gameInfoPanel->updateTurn(++nbTurn);
        }
        break;

        /*----------WaitingAttack----------*/
    case GameState::Waiting:
        if (time >= gameSettings.timeToPlay) {
            gameInfoPanel->updateGameInfo("Your Turn");
            timer.restart();
            gameState = GameState::Attacking;
            gameInfoPanel->updateTurn(++nbTurn);
        }
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

void GameWindow::CreateHud(std::string& enemyInfoMessage)
{
    std::string id;
    std::string ratio;
    std::string score;
    int picture;

    std::stringstream ss(enemyInfoMessage.erase(0, 1));
    std::string item;
    std::vector<std::string> tokens;
    while (std::getline(ss, item, '$')) {
        tokens.push_back(item);
    }

    id = tokens[0];
    ratio = tokens[1];
    score = tokens[2];
    picture = std::stoi(tokens[3]);

    playerHud = new PlayerHud(application->getGameFont(), false, application->getBddObj().getIdPlayers(), application->getBddObj().getRatio(), application->getBddObj().getScore(), application->getChoosenPicture());
    enemyHud = new PlayerHud(application->getGameFont(), true, id, ratio, score, application->getCharactersImgs().at(picture));
    isHudOk = true;

    gameChat = new GameChat(application->client, application->getGameFont(), application->getBddObj().getIdPlayers(), id);
}

void GameWindow::OnEnd(bool isWin)
{
    battleshipCore.SaveEndGame(isWin, application->getBddObj());

    int score = battleshipCore.getEnemyBoatSunk() * 50;
    if (isWin)
    {
        score += 250;
        application->fxobj->createSfx(SfxManager::sfx::victory);
        application->fxobj->createSfx(SfxManager::sfx::voiceVictory);
    }
    else
    {
        application->fxobj->createSfx(SfxManager::sfx::defeat);
        application->fxobj->setSfxVolume(200);
    }

    endPanel->Show(isWin, std::stoi(application->getBddObj().getScore()), score);
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

    gameInfoPanel->draw(window);
    if(isHudOk)
    {
        playerHud->draw(window);
        enemyHud->draw(window);
    }
    endPanel->draw(window);

    if(gameChat != nullptr)
        gameChat->Draw(window);
}
