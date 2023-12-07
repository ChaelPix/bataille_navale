#include "SfmlWindow.h"
#include <iostream>
SfmlWindow::SfmlWindow(const std::string& title, const sf::Vector2f& size)
    : window(sf::VideoMode(size.x, size.y), title) {}

void SfmlWindow::Run() {

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        HandleEvents(event);
    }
    Update(event);

    if (!CheckAlive())
        return;
    else
        Render();
    window.display();
    window.clear(windowSettings.bgColor);

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
