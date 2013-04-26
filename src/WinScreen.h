//
//  WinScreen.h
//

#ifndef SpriteMove_WinScreen_h
#define SpriteMove_WinScreen_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class WinScreen
{
public:
    WinScreen();
    sf::Sprite & getSprite();
    void setLocation(float,float);
    void draw(sf::RenderWindow &win);
private:
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif
