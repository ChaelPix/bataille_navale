#include "SfmlWindow.h"
#include <iostream>
SfmlWindow::SfmlWindow(const std::string& title, const sf::Vector2f& size, const sf::Vector2i& windowPos)
    : window(sf::VideoMode(size.x, size.y), title)
{
    window.setPosition(windowPos);

    sf::Image icon;
    icon.loadFromFile("ressources/appIco.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void SfmlWindow::Run() {

    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            exit(0);
        }

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
    if (elapsedTime.asMilliseconds() < 2) {
        sf::sleep(sf::milliseconds(2) - elapsedTime);
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

