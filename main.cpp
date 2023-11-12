#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Title");

    sf::Event event;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {

                window.close();
            }
        }

        window.clear(sf::Color::White);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            std::cout << "Hello world\n";

        window.display();
    }

    return 0;
}