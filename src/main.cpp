//*******************************************
// A simple space invaders clone using SFML
// Author: mshirlaw
// April 2013
//*******************************************

#include "Bullet.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "LoseScreen.h"
#include "ResourcePath.h"
#include "Ship.h"
#include "SoundManager.h"
#include "WinScreen.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

constexpr unsigned WIDTH = 800;
constexpr unsigned HEIGHT = 600;
constexpr unsigned NUMBER_OF_ALIENS = 7;
constexpr auto ICON_PATH = "win-icon.ico";

int main()
{
    const float shipSpeed = 400.f;
    const int alienMaxSpeed = 1200;
    const int alienMinSpeed = 500;
    const float bulletSpeed = 500.f;
    bool gameOver = false;
    bool winner = false;

    // initialize random seed
    srand(time(nullptr));

    // Create the main window
    sf::RenderWindow window(sf::VideoMode{WIDTH, HEIGHT}, "Space Invaders Clone",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // title bar icon (Windows only)
    sf::Image appIcon;
    if (appIcon.loadFromFile(game::getResourcePath(ICON_PATH)))
    {
        auto dims = appIcon.getSize();
        window.setIcon(dims.x, dims.y, appIcon.getPixelsPtr());
    }

    // start background music
    SoundManager music;
    music.playBackgroundMusic();

    // create background
    sf::Sprite back;
    sf::Texture star;

    // Load background to display
    if (!star.loadFromFile(game::getResourcePath("stars.png")))
        throw std::invalid_argument("Background not loaded!");
    // create sprite and scale
    back.setTexture(star);

    // create win and lose screens
    WinScreen win;
    LoseScreen lose;

    // create a bullet
    Bullet bullet(0, bulletSpeed);

    // create the ship
    Ship myShip(0, shipSpeed);
    myShip.setLocation(WIDTH / 2, HEIGHT - myShip.getSprite().getGlobalBounds().height);

    // create a an array of enemys
    Enemy alienArray[NUMBER_OF_ALIENS];
    for (int i = 0; i < NUMBER_OF_ALIENS; i++)
    {
        Enemy alien(i, alienMinSpeed + (rand() % alienMaxSpeed));
        alien.setLocation(i * 100 + 50, alien.getSprite().getGlobalBounds().height / 2);
        alienArray[i] = alien;
    }

    // main clock for fps
    sf::Clock clock;

    // clock for aliens
    sf::Clock alienClock;
    alienClock.restart().asSeconds();

    // clock for bullet
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

            // Close window : exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Close window : exit
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (gameOver)
                {
                    // (re)start the game
                    gameOver = false;
                    winner = false;
                    clock.restart();

                    // reset aliens
                    for (int i = 0; i < NUMBER_OF_ALIENS; i++)
                    {
                        Enemy alien(i, alienMinSpeed + (rand() % alienMaxSpeed));
                        alien.setLocation(i * 100 + 50, alien.getSprite().getGlobalBounds().height / 2);
                        alienArray[i] = alien;
                    }

                    // reset ship location
                    myShip.setLocation(WIDTH / 2, HEIGHT - myShip.getSprite().getGlobalBounds().height);
                    myShip.respawn();

                    // restart music
                    music.playBackgroundMusic();
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                if (!bullet.isAlive() && !gameOver)
                {
                    bullet.spawn(true);
                    bullet.setLocation(myShip.getSprite().getPosition().x + 31,
                                       myShip.getSprite().getPosition().y - 15);
                    music.playLazer();
                }
            }

            // Escape pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }

        // Clear screen
        window.clear(sf::Color(0, 0, 0, 255));
        window.draw(back);

        // check for movement of ship
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
        {
            if (myShip.getSprite().getPosition().x + myShip.getSprite().getGlobalBounds().width < WIDTH)
            {
                // cout << sprite.getPosition().x << endl;
                myShip.getSprite().move(shipSpeed * deltaTime, 0.f);
            }
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
        {
            if (myShip.getSprite().getPosition().x > 0.f)
            {
                // cout << sprite.getPosition().x << endl;
                myShip.getSprite().move(-shipSpeed * deltaTime, 0.f);
            }
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        {
            if (myShip.getSprite().getPosition().y > 0.f)
            {
                // cout << sprite.getPosition().x << endl;
                myShip.getSprite().move(0.f, -shipSpeed * deltaTime);
            }
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
        {
            if (myShip.getSprite().getPosition().y + myShip.getSprite().getGlobalBounds().height < HEIGHT)
            {
                // cout << sprite.getPosition().x << endl;
                myShip.getSprite().move(0.f, shipSpeed * deltaTime);
            }
        }

        // move aliens
        sf::Time t = alienClock.getElapsedTime();
        // cout<<t.asSeconds()<<endl;
        if (t.asSeconds() > 0.5)
        {
            for (size_t i = 0; i < 7; i++)
            {
                alienArray[i].getSprite().move(0.f, alienArray[i].getSpeed() * deltaTime);
            }
            alienClock.restart();
        }

        sf::Time bc = bulletClock.getElapsedTime();
        if (bc.asSeconds() > 1.0)
        {
            if (bullet.isAlive() && !gameOver)
            {
                // draw bullet
                bullet.draw(window);
                // move bullet
                bullet.getSprite().move(0.f, -20);
            }
        }

        // test collisions between aliens and ships
        for (int i = 0; i < NUMBER_OF_ALIENS; i++)
        {
            if (CollisionManager::collidesWith(myShip, alienArray[i]) && alienArray[i].isAlive())
            {
                if (!gameOver)
                    music.playExplosion();
                myShip.kill();
                winner = false;
                gameOver = true;
            }
        }

        // test collisions between aliens and bottom of screen
        for (int i = 0; i < NUMBER_OF_ALIENS; i++)
        {
            if (alienArray[i].getSprite().getPosition().y + alienArray[i].getSprite().getGlobalBounds().height >
                    HEIGHT &&
                alienArray[i].isAlive())
            {
                if (!gameOver)
                    music.playExplosion();
                winner = false;
                gameOver = true;
            }
        }

        // test collisions between bullet and aliens
        for (int i = 0; i < NUMBER_OF_ALIENS; i++)
        {
            if (CollisionManager::collidesWith(bullet, alienArray[i]) && alienArray[i].isAlive())
            {
                music.playExplosion();
                alienArray[i].kill();
                bullet.kill();
            }
        }

        int deadAliens = 0;
        // test for a winner
        for (int i = 0; i < NUMBER_OF_ALIENS; i++)
        {
            if (!alienArray[i].isAlive())
                deadAliens++;

            if (deadAliens == NUMBER_OF_ALIENS)
            {
                if (!gameOver)
                    // music.playReward();
                    winner = true;
                gameOver = true;
            }
        }

        // test collision with bullet and boundary
        if (bullet.getSprite().getPosition().y < 0)
            bullet.kill();

        // draw to screen
        if (!gameOver)
        {
            for (size_t i = 0; i < NUMBER_OF_ALIENS; i++)
            {
                if (alienArray[i].isAlive())
                {
                    alienArray[i].draw(window);
                }
            }

            if (myShip.isAlive())
            {
                // draw ship
                myShip.draw(window);
            }

            // Update the window
            window.display();
        }
        else
        {
            music.pauseBackgroundMusic();

            if (winner)
                win.draw(window);
            else
                lose.draw(window);

            // Update the window
            window.display();
        }
    }

    return EXIT_SUCCESS;
}
