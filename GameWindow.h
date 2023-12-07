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
#include "CursorCellSelector.h"

class GameWindow : public SfmlWindow {
public:
    GameWindow(GameApplication& application);
    enum class GameState {Placing, WaitingGrid, Attacking, Waiting, Victory, Defeat};
protected:
    void Initialize() override;

    void HandleEvents(sf::Event& event) override;
    
    //TEST HUD
    void SetupHud(const std::string& imagePath, const std::string& fontPath, const std::string& text);
    void Hud();

    void Update(sf::Event& event) override;

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

    CursorCellSelector* cursor;

    //TEST HUD
    sf::Texture hudTexture;
    sf::Sprite hudSprite;
    sf::Font hudFont;
    sf::Text hudText;
};


//"ressources/UI/hud_Player.png"   "ressources/fonts/AGENCYB.TTF"  "Player 1"
