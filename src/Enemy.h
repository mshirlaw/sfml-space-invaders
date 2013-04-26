//
//  Enemy.h
//

#ifndef SpriteMove_Enemy_h
#define SpriteMove_Enemy_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <iostream>
#include <string>

class Enemy
{
public:
    //constructor sets ID number, loads sprite
    Enemy(){};
    Enemy(const int,float);
    sf::Sprite & getSprite();
    void setLocation(float,float);
    void kill();
    bool isAlive();
    void draw(sf::RenderWindow &win);
private:
    sf::Sprite sprite;
    sf::Texture texture;
    bool alive;
};


#endif
