//
//  Bullet.cpp
//

#include "Bullet.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Bullet::Bullet(const int id, float speed)
{
    // alive
    alive = false;

    // load a sprite
    if (!texture.loadFromFile(resourcePath() + "bullet.png"))
        throw invalid_argument("Bullet not loaded!");

    // scale
    sprite.scale(sf::Vector2f(0.3, 0.3));
}

sf::Sprite &Bullet::getSprite()
{
    return sprite;
}

void Bullet::setLocation(float xpos, float ypos)
{
    sprite.setPosition(xpos, ypos);
}

void Bullet::kill()
{
    alive = false;
}

bool Bullet::isAlive()
{
    return alive;
}

void Bullet::spawn(bool bul)
{
    alive = bul;
}

void Bullet::draw(sf::RenderWindow &win)
{
    // set texture
    sprite.setTexture(texture);
    win.draw(sprite);
}
