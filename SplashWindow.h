#pragma once

#include "SfmlWindow.h"
#include "Application.h"

#include "Settings.h"
#include "AnimatedBackground.h"
#include "MouseManager.h"
#include "MenuButtonsManager.h"



class SplashWindow : public SfmlWindow
{
public:
    SplashWindow(GameApplication& application);
    ~SplashWindow();

protected:
    void Initialize() override;

    void HandleEvents(sf::Event& event) override;

    void Update(sf::Event& event) override;

    void Render() override;

    void SplashAnim();

private:
    GameApplication* application;
    SplashSettings splashObj;
    std::vector<EntityRectangle*> entitiesPtr;
    std::vector<EntityRectangle> Logo;
    sf::Texture SplashTexture[2];
    int currentLogoIndex = 0;
    sf::Clock clockSplash;  // Clock to measure elapsed time
    float fadeDuration = 1.0f; // Durée du fondu en secondes
    bool started;
    bool L1 = false; 
    bool L2 = false;
};
