#pragma once

#include <SFML/Graphics.hpp>

struct GridSettings {
    const int squareSize = 500;
    const int nbPixels = 10;
    const int fps = 15;
    const sf::Color lineColor = sf::Color(255, 255, 255, 75);

    const sf::Vector2f playerGridPosition = sf::Vector2f(100, 250);
    const sf::Vector2f ennemyGridPosition = sf::Vector2f(700, 250);
};
