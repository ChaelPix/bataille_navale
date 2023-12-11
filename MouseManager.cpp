#include "MouseManager.h"
#include <iostream>
void MouseManager::update(sf::Event event, sf::RenderWindow& window)
{
    clickPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    std::cout << "mous x : " << clickPosition.x << " y : " << clickPosition.y << std::endl;
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Right) {
            isRClicked = true;
        }
        if (event.mouseButton.button == sf::Mouse::Left) {
            isClicked = true;
        }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Right) {
            isRClicked = false;
        }
        if (event.mouseButton.button == sf::Mouse::Left) {
            isClicked = false;
        }
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

bool MouseManager::isMouseRClicked()
{
    return isRClicked;
}
