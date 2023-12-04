#pragma once

class GameApplication;

#include "Application.h"
#include "PlayerBoatsManager.h"
#include "Grid.h"
#include "Settings.h"
#include "AnimatedBackground.h"
#include "MouseManager.h"
#include "BattleshipCore.h"
#include <vector>

class GameWindow : public SfmlWindow {
public:
    GameWindow(GameApplication& application);

protected:
    void Initialize() override;

    void HandleEvents(sf::Event& event) override;

    void Update() override;

    void Render() override;

private:
    GameApplication* application;

    MouseManager mouseManager;
    GridSettings gridSettings;
    WindowSettings windowSettings;

    AnimatedBackground* waterBackground;

    Grid gridPlayer, gridEnemy;
    PlayerBoatsManager* playerBoatsManager;

    std::vector<Entity*> entitiesPtr;

    BattleshipCore battleshipCore;
};


