//
//  WinScreen.h
//

#ifndef SpriteMove_WinScreen_h
#define SpriteMove_WinScreen_h

#include "ResourcePath.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

class WinScreen
{
  public:
    WinScreen();
    sf::Sprite &getSprite();
    void setLocation(float, float);
    void draw(sf::RenderWindow &win);

  private:
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif
