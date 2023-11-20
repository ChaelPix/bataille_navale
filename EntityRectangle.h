#include "Entity.h"

//hpp, will be changed to h + cpp
class EntityRectangle : public Entity {
private:
    sf::RectangleShape shape;

public:
    EntityRectangle(const sf::Vector2f& size) {
        shape.setSize(size);
        // Autres initialisations
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(shape);
    }

    void update() override {
        // Mettre à jour la logique spécifique du rectangle
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

    sf::RectangleShape getShape()
    {
        return shape;
    }
};
