#pragma once

class GameApplication;

#include "Application.h"
#include "PlayerBoatsManager.h"
#include "Grid.h"
#include "Settings.h"
#include "AnimatedEntity.h"
#include "MouseManager.h"
#include "BattleshipCore.h"
#include "CloudManager.h"
#include "EndPanel.h"
#include "GameVfx.h"
#include <vector>
#include "CursorCellSelector.h"
#include "GameInfoPanel.h"
#include "PlayerHud.h"
#include "GameChat.h"

class GameWindow : public SfmlWindow {
public:
    GameWindow(GameApplication& application, const sf::Vector2i& windowPos);
    enum class GameState {Placing, SynchroGrid, WaitingGrid, Attacking, Waiting, End};
protected:
    void Initialize() override;

    void HandleEvents(sf::Event& event) override;

    void Update(sf::Event& event) override;

    void Render() override;

private:
    int nbTurn = 1;
    CloudManager* cloudManager = new CloudManager();

    GameApplication* application;

    MouseManager mouseManager;
    GridSettings gridSettings;
    WindowSettings windowSettings;
    GameSettings gameSettings;

    AnimatedEntity* waterBackground;

    Grid gridPlayer, gridEnemy;
    PlayerBoatsManager* playerBoatsManager;

    std::vector<Entity*> entitiesPtr;

    BattleshipCore battleshipCore;

    sf::Clock timer;
    GameState gameState;

    CursorCellSelector* cursor;
    EndPanel* endPanel;
    GameVfx* gameVfx;
    GameInfoPanel* gameInfoPanel;
    GameChat* gameChat;

    PlayerHud* playerHud;
    PlayerHud* enemyHud;
    bool isHudOk = false;
    void processMessages();
    void handleGameState();

    void CreateHud(std::string& enemyInfoMessage);
    void OnEnd(bool isWin);
};


