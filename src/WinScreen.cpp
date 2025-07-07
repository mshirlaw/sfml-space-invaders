//
//  WinScreen.cpp
//

#include "WinScreen.h"

WinScreen::WinScreen()
{
    // Load gameOver to display
    if (!texture.loadFromFile(resourcePath() + "you_win.png"))
        throw invalid_argument("Game over screen not loaded!");

    // create sprite and scale
    sprite.scale(sf::Vector2f(1, 1));
    sprite.setPosition(100, 100);
}

sf::Sprite &WinScreen::getSprite()
{
    return sprite;
}

void WinScreen::setLocation(float xpos, float ypos)
{
    sprite.setPosition(xpos, ypos);
}

void WinScreen::draw(sf::RenderWindow &win)
{
    // set texture
    sprite.setTexture(texture);
    win.draw(sprite);
}
