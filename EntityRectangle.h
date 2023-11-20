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
        // Mettre � jour la logique sp�cifique du rectangle
    }

    void setTexture(sf::Texture* texture) {
        shape.setTexture(texture);
    }
    // Autres m�thodes sp�cifiques � EntityRectangle
};
