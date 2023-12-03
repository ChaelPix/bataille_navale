#include "SfmlWindow.h"
#include <iostream>
SfmlWindow::SfmlWindow(const std::string& title, const sf::Vector2f& size)
    : window(sf::RenderWindow(sf::VideoMode(size.x, size.y), title)) {}

void SfmlWindow::Run() {

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            HandleEvents(event);
        }
        Update();
        Render();
        window.display();
        window.clear(windowSettings.bgColor);
    }
}
