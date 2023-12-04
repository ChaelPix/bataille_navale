#pragma once

class GameApplication;

#include "Application.h"
#include "PlayerBoatsManager.h"
#include "Grid.h"
#include "Settings.h"
#include "AnimatedBackground.h"
#include "MouseManager.h"
#include "BattleshipCore.h"
#include "CloudManager.h"
#include <vector>

class GameWindow : public SfmlWindow {
public:
    GameWindow(GameApplication& application);
    enum class GameState {Placing, Attacking, Waiting, Victory, Defeat};
protected:
    void Initialize() override;

    void HandleEvents(sf::Event& event) override;

    void Update() override;

    void Render() override;

private:
    CloudManager* cloudManager = new CloudManager();

    GameApplication* application;

    MouseManager mouseManager;
    GridSettings gridSettings;
    WindowSettings windowSettings;

    AnimatedBackground* waterBackground;

    Grid gridPlayer, gridEnemy;
    PlayerBoatsManager* playerBoatsManager;

    std::vector<Entity*> entitiesPtr;

    BattleshipCore battleshipCore;

    sf::Clock timer;
    GameState gameState;
};


