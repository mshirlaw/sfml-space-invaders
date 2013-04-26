//
//  CollisionManager.cpp
//

#include "CollisionManager.h"

bool CollisionManager::collidesWith(Ship &obj1, Enemy &obj2)
{
    //get the bounding box of the ship
    sf::FloatRect ship;
    //top left
    ship.left = obj1.getSprite().getPosition().x+10;
    ship.top = obj1.getSprite().getPosition().y+10;
    //bottom right
    ship.width = obj1.getSprite().getGlobalBounds().width-10;
    ship.height = obj1.getSprite().getGlobalBounds().height-10;
    
    //get the bounding box of the alien
    sf::FloatRect alien;
    //top left
    alien.left = obj2.getSprite().getPosition().x;
    alien.top = obj2.getSprite().getPosition().y;
    //bottom right
    alien.width = obj2.getSprite().getGlobalBounds().width;
    alien.height =obj2.getSprite().getGlobalBounds().height;

    //std::cout << "Ship left: " << ship.left << " " << "Ship top: " << ship.top << std::endl;
    //std::cout << "Alien left: " << alien.left << " " << "Alien top: " << alien.top << std::endl;
        
    return ship.intersects(alien);
    
}

bool CollisionManager::collidesWith(Bullet &obj1, Enemy &obj2)
{
    //get the bounding box of the ship
    sf::FloatRect bullet;
    //top left
    bullet.left = obj1.getSprite().getPosition().x+10;
    bullet.top = obj1.getSprite().getPosition().y+10;
    //bottom right
    bullet.width = obj1.getSprite().getGlobalBounds().width-10;
    bullet.height = obj1.getSprite().getGlobalBounds().height-10;
    
    //get the bounding box of the alien
    sf::FloatRect alien;
    //top left
    alien.left = obj2.getSprite().getPosition().x;
    alien.top = obj2.getSprite().getPosition().y;
    //bottom right
    alien.width = obj2.getSprite().getGlobalBounds().width;
    alien.height =obj2.getSprite().getGlobalBounds().height;
    
    //std::cout << "Ship left: " << ship.left << " " << "Ship top: " << ship.top << std::endl;
    //std::cout << "Alien left: " << alien.left << " " << "Alien top: " << alien.top << std::endl;
    
    return bullet.intersects(alien);
    
}
