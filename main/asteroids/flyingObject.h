/*************************************************************
 * File: flyingObject.h
 * Author: Caleb Hensley
 *
 * Description: Defines a FlyingObject.
 *
 * Flying object is a base class for any flying object.
 * in Asteroids, this will be a bullet, ship, and rock
 *************************************************************/

#ifndef FLYING_OBJECT_H
#define FLYING_OBJECT_H

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

#define WORLD_SIZE 127

#include <vector>
using namespace std;

class FlyingObject
{
protected:
   Point point;
   Velocity velocity;
   bool alive;
   float rotation;
   float radius;

public:
   FlyingObject();
   FlyingObject(Point point);
   Point getPoint() const { return point; }
   Velocity getVelocity() const { return velocity; }
   bool isAlive() const { return alive; }
   void setPoint(Point point);
   void setVelocity(Velocity velocity);
   void setAlive(bool alive);
   void kill();
   void advance();
   
   virtual void draw() = 0;

   // these are the functions I've added in this project
   void rotate(float rotation);
   void setRotation(float rotation) { this->rotation = rotation; }
   float getRotation() { return rotation; }
   float getRadius() { return radius; }
   void setRadius(float radius) { this->radius = radius; }
   void stayInWorld();
};

#endif
