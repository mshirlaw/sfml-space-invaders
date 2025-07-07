//
//  LoseScreen.h
//

#ifndef SpriteMove_LoseScreen_h
#define SpriteMove_LoseScreen_h

#include "ResourcePath.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <string>


class LoseScreen
{
  public:
    LoseScreen();
    sf::Sprite &getSprite();
    void setLocation(float, float);
    void draw(sf::RenderWindow &win);

  private:
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif