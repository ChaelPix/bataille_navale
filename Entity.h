#ifndef _Entity
#define _Entity

#pragma once

#include "Settings.h"
#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update() = 0;

    virtual ~Entity() {} 
};

#endif