#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Settings.h"
#include "sfxManager.h"

class SfmlWindow
{
protected:
    virtual void Initialize() = 0;
    virtual void Update(sf::Event& event) = 0;
    virtual void Render() = 0;
    virtual void HandleEvents(sf::Event& event) = 0;

    sf::RenderWindow window;
    WindowSettings windowSettings;
    bool running = true;
    sf::Clock clock;
public:
    SfmlWindow(const std::string& title, const sf::Vector2f& size, const sf::Vector2i& windowPos);

    virtual ~SfmlWindow() = default;

    void Run();
    virtual bool CheckAlive();
    void Stop();
    sf::Vector2i GetWindowPosition();

    std::string wName = "sfml";
};

