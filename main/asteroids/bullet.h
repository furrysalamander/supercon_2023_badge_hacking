/*************************************************************
 * File: bullet.h
 * Author: Caleb Hensley
 *
 * Description: Defines a Bullet.
 *
 * Bullet will be able to fire from the rifle, and die if it
 * hits a rock
 *************************************************************/

#ifndef BULLET_H
#define BULLET_H

#define BULLET_SPEED 5
#define BULLET_LIFE 60

#include "flyingObject.h"
#include "uiDraw.h"

class Bullet : public FlyingObject
{
private:
   int ttl;
public:
   Bullet();
   Bullet(Point shipPoint, float angle, Velocity shipVel);
   void draw();
   void fire(Point point, float angle, Velocity shipVel);
};

#endif
