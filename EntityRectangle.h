#ifndef _ENTITYRECTANGLE_H
#define _ENTITYRECTANGLE_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <string>

class EntityRectangle : public Entity {
protected:
    sf::RectangleShape shape;
    sf::Texture shapeTexture;

public:
    EntityRectangle(const sf::Vector2f& size);
    EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position);
    EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, std::string texturePath);
    EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, std::string texturePath, const sf::Vector2f& origin);
    EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, sf::Texture texture);
    EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, sf::Texture texture, sf::Color color);
    EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, sf::Color color);
    EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, sf::Texture texture, float angleDegres, const sf::Vector2f& origin);

    virtual void draw(sf::RenderWindow& window);

    void setTexture(sf::Texture* texture);
    void setPosition(sf::Vector2f position);
    void setPosition(float x, float y);
    sf::Vector2f getPosition();
    void rotate(float angleTarget);
    void setOrigin(sf::Vector2f origin);
    void move(sf::Vector2f vel);
    void move(float velX, float velY);
    void setColor(sf::Color color);
    sf::Color getColor() const;
    sf::RectangleShape getShape();
    sf::Vector2f getSize();
};

#endif
