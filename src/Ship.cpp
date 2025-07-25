//
//  Ship.cpp
//

#include "Ship.h"
#include <iostream>
#include <stdexcept>

// constructor sets ID number, loads sprite
Ship::Ship(const int id, float speed)
{
    alive = true;

    // Load a Ship to display
    if (!texture.loadFromFile(game::getResourcePath("medium_ship.png")))
        throw std::invalid_argument("Ship not loaded!");

    // create sprite and set texture so we know its size
    sprite.setTexture(texture);
    sprite.scale(sf::Vector2f(0.4f, 0.4f));
}

void Ship::setLocation(float xpos, float ypos)
{
    sprite.setPosition(xpos, ypos);
}

sf::Sprite &Ship::getSprite()
{
    return sprite;
}

void Ship::kill()
{
    alive = false;
}

bool Ship::isAlive()
{
    return alive;
}

void Ship::draw(sf::RenderWindow &win)
{
    // set texture
    sprite.setTexture(texture);
    win.draw(sprite);
}

void Ship::respawn()
{
    alive = true;
}