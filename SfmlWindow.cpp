#include "SfmlWindow.h"
#include <iostream>
SfmlWindow::SfmlWindow(const std::string& title, const sf::Vector2f& size)
    : window(sf::VideoMode(size.x, size.y), title) {}

void SfmlWindow::Run() {

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            HandleEvents(event);
        }
        Update();
        if (!running)
            break;
        Render();
        window.display();
        window.clear(windowSettings.bgColor);

        //sf::Clock clock;
        //// Attendre 1/60ème de seconde (60 FPS)
        //sf::Time elapsedTime = clock.getElapsedTime();
        //if (elapsedTime.asMilliseconds() < 16)
        //{
        //    sf::sleep(sf::milliseconds(16) - elapsedTime);
        //}
        //clock.restart();

    }
}
