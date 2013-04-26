//*******************************************
//A simple space invaders clone using SFML
//Author: mshirlaw
//April 2013
//*******************************************

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include "Ship.h"
#include "Enemy.h"
#include "Bullet.h"
#include "WinScreen.h"
#include "LoseScreen.h"
#include "CollisionManager.h"

#define WIDTH 800
#define HEIGHT 600
#define NUMBER_OF_ALIENS 7
using namespace std;

const float shipSpeed = 500.f;
const float alienSpeed = 500.f;
const float bulletSpeed = 500.f;
bool gameOver=false;
bool winner = false;

int main(int, char *argv[])
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Space Invaders Clone");
    window.setVerticalSyncEnabled(true);

    //create background
    sf::Sprite back;
    sf::Texture star;
    
    // Load background to display
    if(!star.loadFromFile(resourcePath() + "stars.png"))
        throw invalid_argument("Background not loaded!");
    //create sprite and scale
    back.setTexture(star);
    
    //create win and lose screens
    WinScreen win;
    LoseScreen lose;
    
    //create a bullet
    Bullet bullet(0,bulletSpeed);

    //create the ship
    Ship myShip(0,shipSpeed);
    myShip.setLocation(WIDTH/2,HEIGHT-myShip.getSprite().getGlobalBounds().height);

    //create a an array of enemys
    Enemy alienArray[NUMBER_OF_ALIENS];
    for(int i=0; i<NUMBER_OF_ALIENS; i++)
    {
        Enemy alien(i,alienSpeed);
        alien.setLocation(i*100+50, alien.getSprite().getGlobalBounds().height/2);
        alienArray[i] = alien;
    }

    //main clock for fps
    sf::Clock clock;
    
    //clock for aliens
    sf::Clock alienClock;
    alienClock.restart().asSeconds();

    //clock for bullet
    sf::Clock bulletClock;
    bulletClock.restart().asSeconds();
    
    // Start the game loop
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            //check for movement of ship
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
            {
                if (myShip.getSprite().getPosition().x + myShip.getSprite().getGlobalBounds().width < WIDTH)
                {
                    //cout << sprite.getPosition().x << endl;
                    myShip.getSprite().move(shipSpeed * deltaTime, 0.f);
                }
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
            {
                if(myShip.getSprite().getPosition().x > 0.f)
                {
                    //cout << sprite.getPosition().x << endl;
                    myShip.getSprite().move(-shipSpeed * deltaTime, 0.f);
                }
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            {
                if(myShip.getSprite().getPosition().y > 0.f)
                {
                    //cout << sprite.getPosition().x << endl;
                    myShip.getSprite().move( 0.f,-shipSpeed * deltaTime);
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            {
                if(myShip.getSprite().getPosition().y + myShip.getSprite().getGlobalBounds().height < HEIGHT)
                {
                    //cout << sprite.getPosition().x << endl;
                    myShip.getSprite().move(0.f, shipSpeed * deltaTime);
                }
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                if(!bullet.isAlive())
                {
                    bullet.spawn(true);
                    bullet.setLocation(myShip.getSprite().getPosition().x+31,myShip.getSprite().getPosition().y-15);
                }
            }
            
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Close window : exit
            if (event.type == sf::Event::MouseButtonPressed) {
                if(gameOver)
                    window.close();
            }
            
            // Espace pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        // Clear screen
        window.clear(sf::Color(0,0,0,255));
        window.draw(back);
        
        
        //move aliens
        sf::Time t = alienClock.getElapsedTime();
        //cout<<t.asSeconds()<<endl;
        if(t.asSeconds() > 0.5)
        {
            for(size_t i=0; i<7; i++)
            {
                alienArray[i].getSprite().move(0.f,10);
            }
            alienClock.restart();
        }

        sf::Time bc = bulletClock.getElapsedTime();
        if(bc.asSeconds() > 1.0)
        {
            if(bullet.isAlive())
            {
                //draw bullet
                bullet.draw(window);
                //move bullet
                bullet.getSprite().move(0.f,-20);
            }
        }

        //test collisions between aliens and ships
        for(int i=0; i<NUMBER_OF_ALIENS;i++)
        {
            if(CollisionManager::collidesWith(myShip, alienArray[i]) && alienArray[i].isAlive())
            {
                myShip.kill();
                winner=false;
                gameOver=true;
            }
        }
        
        //test collisions between aliens and bottom of screen
        for(int i=0; i<NUMBER_OF_ALIENS;i++)
        {
            if(alienArray[i].getSprite().getPosition().y>HEIGHT && alienArray[i].isAlive())
            {
                winner=false;
                gameOver=true;
            }
        }
        
        //test collisions between bullet and aliens
        for(int i=0; i<NUMBER_OF_ALIENS;i++)
        {
            if(CollisionManager::collidesWith(bullet, alienArray[i]) && alienArray[i].isAlive())
            {
                alienArray[i].kill();
                bullet.kill();
            }
        }
        
        int deadAliens=0;
        //test for a winner
        for(int i=0; i<NUMBER_OF_ALIENS; i++)
        {
            if(!alienArray[i].isAlive())
                deadAliens++;
            
            if(deadAliens==NUMBER_OF_ALIENS)
            {
                winner=true;
                gameOver=true;
            }
        }
                
        //test collision with bullet and boundary
        if(bullet.getSprite().getPosition().y < 0)
            bullet.kill();
        
        
        //draw to screen
        if(!gameOver)
        {
            for(size_t i=0;i<NUMBER_OF_ALIENS;i++)
            {
                if(alienArray[i].isAlive())
                {
                    alienArray[i].draw(window);
                }
            }

            if(myShip.isAlive())
            {
                //draw ship
                myShip.draw(window);
            }
        
            // Update the window
            window.display();
        }
        else
        {
            if(winner)
                win.draw(window);
            else
                lose.draw(window);
                
            // Update the window
            window.display();
        }
        
    }
    
    return EXIT_SUCCESS;
}

void testCollisions()
{
    
}
