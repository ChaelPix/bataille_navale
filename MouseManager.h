#pragma once
#include <SFML/Graphics.hpp>

class MouseManager
{

private:
    sf::Vector2i clickPosition;
    bool isClicked = false;

public:
    void update(sf::Event event, sf::RenderWindow& window);

    sf::Vector2i getClickPosition();
    bool isMouseClicked();

};

