#pragma once
#include "Entity.h"


class EntityText : public Entity
{

protected:
    sf::Text Text;

public:
    EntityText(sf::Font &font, int size, std::string text);
    EntityText(sf::Font &font, const sf::Vector2f position, const int size, std::string text);
    EntityText(sf::Font& font, const sf::Vector2f position, const int size, sf::Color color);

    void SetText(std::string txt);
    void SetTextAndCenter(std::string txt);

    void SetPosition(sf::Vector2f position);
    void SetPosition(float posX, float posY);

    void SetCharacterSize(int size);

    void SetColor(sf::Color color);

    void draw(sf::RenderWindow& window) override;

    sf::Text getText();

    float getWidth();
    float getHeight();
};

