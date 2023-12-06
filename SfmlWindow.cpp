#include "SfmlWindow.h"
#include <iostream>
SfmlWindow::SfmlWindow(const std::string& title, const sf::Vector2f& size)
    : window(sf::VideoMode(size.x, size.y), title) {}

void SfmlWindow::Run() {

    sf::Clock frameClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            HandleEvents(event);
        }
        Update(event);

        if (!running)
            break;

        window.clear(windowSettings.bgColor);
        Render();
        window.display();

        sf::Time frameTime = frameClock.restart();
        sf::Time timePerFrame = sf::milliseconds(16); 
        if (frameTime < timePerFrame) {
            sf::sleep(timePerFrame - frameTime);
        }
    }
}
