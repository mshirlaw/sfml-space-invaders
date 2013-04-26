//
//  Enemy.cpp
//

#include "Enemy.h"
#include <iostream>
#include <stdexcept>

using namespace std;

//constructor sets ID number, loads sprite
Enemy::Enemy(const int id,float speed)
{
    //set alive
    alive = true;

    // Load an enemy texture
    if(!texture.loadFromFile(resourcePath() + "alien_100.png"))
        throw invalid_argument("Enemy not loaded!");
    
    //scale sprite and set texture so we know size
    sprite.setTexture(texture);
    sprite.scale(sf::Vector2f(0.8,0.8));
}

sf::Sprite & Enemy::getSprite()
{
    return sprite;
}

void Enemy::setLocation(float xpos, float ypos)
{
    sprite.setPosition(xpos,ypos);
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
    //set texture
    sprite.setTexture(texture);
    //draw
    win.draw(sprite);
}