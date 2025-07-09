//
//  CollisionManager.h
//

#ifndef SpriteMove_CollisionManager_h
#define SpriteMove_CollisionManager_h

#include "Bullet.h"
#include "Enemy.h"
#include "Ship.h"
#include <iostream>

class CollisionManager
{
  public:
    static bool collidesWith(Ship &, Enemy &);
    static bool collidesWith(Bullet &, Enemy &);

  private:
};

#endif
