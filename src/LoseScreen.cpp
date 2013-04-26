//
//  LoseScreen.cpp
//  SpriteMove
//
//  Created by Matt Shirlaw on 26/04/13.
//  Copyright (c) 2013 mshirlaw. All rights reserved.
//

#include "LoseScreen.h"

LoseScreen::LoseScreen()
{
    // Load gameOver to display
    if(!texture.loadFromFile(resourcePath() + "you_lose.png"))
        throw invalid_argument("Game over screen not loaded!");
    
    //create sprite and scale
    sprite.setTexture(texture);
    sprite.scale(sf::Vector2f(1,1));
    sprite.setPosition(100,100);
}

sf::Sprite &LoseScreen::getSprite()
{
    return sprite;
}

void LoseScreen::setLocation(float xpos,float ypos)
{
    sprite.setPosition(xpos,ypos);
}

void LoseScreen::draw(sf::RenderWindow &win)
{
    //set texture
    sprite.setTexture(texture);
    win.draw(sprite);
}

