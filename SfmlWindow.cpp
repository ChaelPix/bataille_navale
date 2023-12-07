#include "SfmlWindow.h"
#include <iostream>
SfmlWindow::SfmlWindow(const std::string& title, const sf::Vector2f& size)
    : window(sf::VideoMode(size.x, size.y), title) {}

void SfmlWindow::Run() {

    sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 FPS
    sf::Clock frameClock;

    //window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        sf::Time startTime = frameClock.getElapsedTime();

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

        //sf::Time usedTime = frameClock.getElapsedTime() - startTime;
        //if (usedTime < timePerFrame) {
        //    sf::sleep(timePerFrame - usedTime);
        //}
        //frameClock.restart();
    }
}
