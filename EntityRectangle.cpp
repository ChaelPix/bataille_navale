#include "EntityRectangle.h"
#include <iostream>

EntityRectangle::EntityRectangle(const sf::Vector2f& size) {
    shape.setSize(size);
}

EntityRectangle::EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position) {
    shape.setSize(size);
    shape.setPosition(position);
}

EntityRectangle::EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, std::string texturePath) {
    shape.setSize(size);
    shape.setPosition(position);
    shapeTexture.loadFromFile(texturePath);
    setTexture(&(this->shapeTexture));
}

EntityRectangle::EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, std::string texturePath, const sf::Vector2f& origin) {
    shape.setSize(size);
    shape.setPosition(position);
    shapeTexture.loadFromFile(texturePath);
    shape.setOrigin(origin);
    setTexture(&(this->shapeTexture));
}

EntityRectangle::EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, sf::Texture texture) {
    shape.setSize(size);
    shape.setPosition(position);
    shapeTexture = texture;
    setTexture(&(this->shapeTexture));
}

EntityRectangle::EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, sf::Texture texture, sf::Color color) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(color);
    shapeTexture = texture;
    setTexture(&(this->shapeTexture));
}

EntityRectangle::EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, sf::Color color)
{
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(color);
}

EntityRectangle::EntityRectangle(const sf::Vector2f& size, const sf::Vector2f& position, sf::Texture texture, float angleDegres, const sf::Vector2f& origin) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setRotation(angleDegres);
    shapeTexture = texture;
    shape.setOrigin(origin);
    setTexture(&(this->shapeTexture));
}

void EntityRectangle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void EntityRectangle::setTexture(sf::Texture* texture) {
    shapeTexture = *texture;
    shape.setTexture(texture);
}

void EntityRectangle::setPosition(sf::Vector2f position) {
    shape.setPosition(position);
}

void EntityRectangle::setPosition(float x, float y) {
    shape.setPosition(sf::Vector2f(x, y));
}

sf::Vector2f EntityRectangle::getPosition() {
    return shape.getPosition();
}

void EntityRectangle::rotate(float angleTarget) {
    shape.setRotation(angleTarget);
}

void EntityRectangle::setOrigin(sf::Vector2f origin) {
    shape.setOrigin(origin);
}

void EntityRectangle::move(sf::Vector2f vel) {
    sf::Vector2f pos = shape.getPosition();
    pos += vel;
    shape.setPosition(pos);
}

void EntityRectangle::move(float velX, float velY) {
    sf::Vector2f pos = shape.getPosition();
    pos += sf::Vector2f(velX, velY);
    shape.setPosition(pos);
}

void EntityRectangle::setColor(sf::Color color) {
    shape.setFillColor(color);
}

sf::Color EntityRectangle::getColor() const {
    return shape.getFillColor();
}

sf::RectangleShape EntityRectangle::getShape() {
    return shape;
}

sf::Vector2f EntityRectangle::getSize()
{
    return shape.getSize();
}
