#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Settings.h"

class SfmlWindow
{
protected:
    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void HandleEvents(sf::Event& event) = 0;

    sf::RenderWindow window;
    WindowSettings windowSettings;
public:
    SfmlWindow(const std::string& title, const sf::Vector2f& size);

    virtual ~SfmlWindow() = default;

    void Run();

};

