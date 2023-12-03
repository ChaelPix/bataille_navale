#pragma once

#include "SfmlWindow.h"
#include "Application.h"

#include "Settings.h"
#include "AnimatedBackground.h"
#include "MouseManager.h"

class MenuWindow : public SfmlWindow
{
public:
    MenuWindow(GameApplication& application);

protected:
    void Initialize() override;

    void HandleEvents(sf::Event& event) override;

    void Update() override;

    void Render() override;

private:
    GameApplication* application;

    MouseManager mouseManager;
    AnimatedBackground* menuBackground;

};

