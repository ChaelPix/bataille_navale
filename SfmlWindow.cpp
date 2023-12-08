#include "SfmlWindow.h"
#include <iostream>
SfmlWindow::SfmlWindow(const std::string& title, const sf::Vector2f& size, const sf::Vector2i& windowPos)
    : window(sf::VideoMode(size.x, size.y), title) 
{
    window.setPosition(windowPos);
}

void SfmlWindow::Run() {

    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        HandleEvents(event);
    }

    Update(event);

    if (!running)
        return;
    else
        Render();

    window.display();
    window.clear(windowSettings.bgColor);

    //fps test
    sf::Time elapsedTime = clock.getElapsedTime();
    if (elapsedTime.asMilliseconds() < 1)
    {
        sf::sleep(sf::milliseconds(1) - elapsedTime);
    }
    clock.restart();

}

sf::Vector2i SfmlWindow::GetWindowPosition()
{
    return window.getPosition();
}

bool SfmlWindow::CheckAlive()
{
    return running && window.isOpen();
}

void SfmlWindow::Stop()
{
    running = false;
    window.close();
}

