#pragma once
#include "Entity.h"


class EntityText : public Entity
{

protected:
    sf::Text Text;

public:
    EntityText(sf::Font &font, sf::Vector2f position, int size, std::string text);

    void SetText(std::string txt);

    void SetPosition(sf::Vector2f position);
    void SetPosition(float posX, float posY);

    void SetCharacterSize(int size);

    void SetColor(sf::Color color);
};

