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
#include <vector>
#include "CursorCellSelector.h"

class GameWindow : public SfmlWindow {
public:
    GameWindow(GameApplication& application, const sf::Vector2i& windowPos);
    enum class GameState {Placing, WaitingGrid, Attacking, Waiting, End};
protected:
    void Initialize() override;

    void HandleEvents(sf::Event& event) override;

    void Update(sf::Event& event) override;

    void Render() override;

private:
    CloudManager* cloudManager = new CloudManager();

    GameApplication* application;

    MouseManager mouseManager;
    GridSettings gridSettings;
    WindowSettings windowSettings;

    AnimatedEntity* waterBackground;

    Grid gridPlayer, gridEnemy;
    PlayerBoatsManager* playerBoatsManager;

    std::vector<Entity*> entitiesPtr;

    BattleshipCore battleshipCore;

    sf::Clock timer;
    GameState gameState;

    CursorCellSelector* cursor;
    EndPanel* endPanel;
};


