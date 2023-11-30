#include "MouseManager.h"

void MouseManager::update(sf::Event event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        clickPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        isClicked = true;
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        isClicked = false;
    }
}

sf::Vector2f MouseManager::getClickPosition()
{
    return clickPosition;
}

bool MouseManager::isMouseClicked()
{
    return isClicked;
}
