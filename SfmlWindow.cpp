#include "SfmlWindow.h"
#include <iostream>
SfmlWindow::SfmlWindow(const std::string& title, const sf::Vector2f& size)
    : window(sf::VideoMode(size.x, size.y), title) {}

void SfmlWindow::Run() {

    //window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(true);

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

       // std::cout << wName << std::endl;

        if (this == nullptr)
            break;

        Render();
        window.display();
        window.clear(windowSettings.bgColor);

        //sf::Time usedTime = frameClock.getElapsedTime() - startTime;
        //if (usedTime < timePerFrame) {
        //    sf::sleep(timePerFrame - usedTime);
        //}
        //frameClock.restart();
    }
}

void SfmlWindow::Stop()
{
    window.close();
}
