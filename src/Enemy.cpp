//
//  Enemy.cpp
//

#include "Enemy.h"
#include <iostream>
#include <stdexcept>

// constructor sets ID number, loads sprite
Enemy::Enemy(const int id, float sp)
{
    // set alive
    alive = true;

    // set speed
    speed = sp;

    // Load an enemy texture
    if (!texture.loadFromFile(game::getResourcePath("alien_100.png")))
        throw std::invalid_argument("Enemy not loaded!");

    // scale sprite and set texture so we know size
    sprite.setTexture(texture);
    sprite.scale(sf::Vector2f(0.8, 0.8));
}

sf::Sprite &Enemy::getSprite()
{
    return sprite;
}

void Enemy::setLocation(float xpos, float ypos)
{
    sprite.setPosition(xpos, ypos);
}

void Enemy::kill()
{
    alive = false;
}

bool Enemy::isAlive()
{
    return alive;
}

void Enemy::draw(sf::RenderWindow &win)
{
    // set texture
    sprite.setTexture(texture);
    // draw
    win.draw(sprite);
}

float Enemy::getSpeed() const
{
    return speed;
}