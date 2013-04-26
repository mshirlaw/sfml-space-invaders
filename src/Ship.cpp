//
//  Ship.cpp
//

#include "Ship.h"
#include <iostream>
#include <stdexcept>

using namespace std;

//constructor sets ID number, loads sprite
Ship::Ship(const int id,float speed)
{
    alive=true;
    
    // Load a Ship to display
    if(!texture.loadFromFile(resourcePath() + "medium_ship.png"))
       throw invalid_argument("Ship not loaded!");
    
    //create sprite and set texture so we know its size
    sprite.setTexture(texture);
    sprite.scale(sf::Vector2f(0.4,0.4));
}

void Ship::setLocation(float xpos, float ypos)
{
    sprite.setPosition(xpos,ypos);
}

sf::Sprite & Ship::getSprite()
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
    //set texture
    sprite.setTexture(texture);
    win.draw(sprite);
}

void Ship::respawn()
{
    alive=true;
}