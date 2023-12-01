#ifndef _EntityR
#define _EntityR

#include "Entity.h"


class EntityRectangle : public Entity {

protected:
    sf::RectangleShape shape;

public:
    EntityRectangle(const sf::Vector2f& size) {
        shape.setSize(size);
    }

    virtual void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    void update() override {
        
    }

    void setTexture(sf::Texture* texture) {
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

    sf::RectangleShape getShape()
    {
        return shape;
    }
};
#endif