#ifndef _EntityR
#define _EntityR

#include "Entity.h"


class EntityRectangle : public Entity {

protected:
    sf::RectangleShape shape;
    sf::Texture shapeTexture;

public:
    EntityRectangle(const sf::Vector2f& size) {
        shape.setSize(size);
    }
    EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position) {
        shape.setSize(size);
        shape.setPosition(position);
    }
    EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, std::string texturePath) {
        shape.setSize(size);
        shape.setPosition(position);
        shapeTexture.loadFromFile(texturePath);
        setTexture(&(this->shapeTexture));
    }
    EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, sf::Texture texture) {
        shape.setSize(size);
        shape.setPosition(position);

        shapeTexture = texture;
        setTexture(&(this->shapeTexture));
    }
    EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, sf::Texture texture, float angleDegres, const sf::Vector2f& origin) {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setRotation(angleDegres);
        shapeTexture = texture;
        shape.setOrigin(origin);
        setTexture(&(this->shapeTexture));
    }

    virtual void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    void update() override {
        
    }

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

    void rotate(float angleTarget)
    {
        shape.setRotation(angleTarget);
    }

    void setOrigin(sf::Vector2f origin)
    {
        shape.setOrigin(origin);
    }

    sf::RectangleShape getShape()
    {
        return shape;
    }
};
#endif