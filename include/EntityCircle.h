#pragma once
#include "Entity.h"
class EntityCircle : public Entity
{
protected:
    sf::CircleShape shape;
    sf::Texture shapeTexture;

public:
    EntityCircle(const int& size) {
        shape.setRadius(size);
    }

    EntityCircle(const int& size, const sf::Vector2f& position) {
        shape.setRadius(size);
        shape.setPosition(position);
    }
    EntityCircle(const int& size, const sf::Vector2f& position, std::string texturePath) {
        shape.setRadius(size);
        shape.setPosition(position);
        shapeTexture.loadFromFile(texturePath);
        setTexture(&(this->shapeTexture));
    }
    EntityCircle(const int size, const sf::Vector2f& position, sf::Texture texture) {
        shape.setRadius(size);
        shape.setPosition(position);

        shapeTexture = texture;
        std::cout << "text load\n";
        setTexture(&(this->shapeTexture));
    }
    EntityCircle(const int& size, const sf::Vector2f& position, sf::Texture texture, sf::Color color) {
        shape.setRadius(size);
        shape.setPosition(position);
        shape.setFillColor(color);
        shapeTexture = texture;
        setTexture(&(this->shapeTexture));
    }
    EntityCircle(const int& size, const sf::Vector2f& position, sf::Texture texture, float angleDegres, const sf::Vector2f& origin) {
        shape.setRadius(size);
        shape.setPosition(position);
        shape.setRotation(angleDegres);
        shapeTexture = texture;
        shape.setOrigin(origin);
        setTexture(&(this->shapeTexture));
    }

    virtual void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    //void update() override {

    //}

    void setTexture(sf::Texture* texture) {
        shapeTexture = *texture;
        shape.setTexture(texture);
    }

    void setPosition(sf::Vector2f position)
    {
        shape.setPosition(position);
    }

    void setPosition(float x, float y)
    {
        shape.setPosition(sf::Vector2f(x, y));
    }

    sf::Vector2f getPosition()
    {
        return shape.getPosition();
    }

    void rotate(float angleTarget)
    {
        shape.setRotation(angleTarget);
    }

    void setOrigin(sf::Vector2f origin)
    {
        shape.setOrigin(origin);
    }

    void move(sf::Vector2f vel)
    {
        sf::Vector2f pos = shape.getPosition();
        pos += vel;
        shape.setPosition(pos);
    }

    void move(float velX, float velY)
    {
        sf::Vector2f pos = shape.getPosition();
        pos += sf::Vector2f(velX, velY);
        shape.setPosition(pos);
    }

    void setColor(sf::Color color)
    {
        shape.setFillColor(color);
    }

    sf::CircleShape getShape()
    {
        return shape;
    }
};

