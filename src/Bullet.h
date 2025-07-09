//
//  Bullet.h
//

#ifndef SpriteMove_Bullet_h
#define SpriteMove_Bullet_h

#include "ResourcePath.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Bullet
{
  public:
    // constructor sets ID number, loads sprite
    Bullet(const int, float);
    sf::Sprite &getSprite();
    void setLocation(float, float);
    void kill();
    bool isAlive();
    void spawn(bool);
    // draw the sprite
    void draw(sf::RenderWindow &win);

  private:
    sf::Sprite sprite;
    sf::Texture texture;
    bool alive;
};

#endif
