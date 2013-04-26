//
//  CollisionManager.h
//

#ifndef SpriteMove_CollisionManager_h
#define SpriteMove_CollisionManager_h

#include "Ship.h"
#include "Enemy.h"
#include "Bullet.h"
#include <iostream>

class CollisionManager
{
public:
    static bool collidesWith(Ship &, Enemy &);
    static bool collidesWith(Bullet &, Enemy &);

private:
};

#endif
