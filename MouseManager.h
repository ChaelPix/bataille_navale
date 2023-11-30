#pragma once
#include <SFML/Graphics.hpp>

class MouseManager
{

private:
    sf::Vector2f clickPosition;
    bool isClicked = false;

public:
    void update(sf::Event event, sf::RenderWindow& window);

    sf::Vector2f getClickPosition();
    bool isMouseClicked();

};

