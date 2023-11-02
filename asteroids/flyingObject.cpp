/*************************************************************
 * File: flyingObject.cpp
 * Author: Caleb Hensley
 *
 * Description: Contains the implementations of the
 *  method bodies for the FlyingObject class
 *
 *************************************************************/

#include "flyingObject.h"

// default constructor setting the flying object to alive
FlyingObject::FlyingObject()
{
   setRotation(0);
   setAlive(true);
}

// non-default constructor initializing point and alive
FlyingObject::FlyingObject(Point point)
{
   setRotation(0);
   setPoint(point);
   setAlive(true);
}
 
// self-explanatory
void FlyingObject::setPoint(Point point)
{
   this->point = point;
}

// self-explanatory
void FlyingObject::setVelocity(Velocity velocity)
{
   this->velocity = velocity;
}

// self-explanatory
void FlyingObject::setAlive(bool alive)
{
   this->alive = alive;
}

// immediately kills object
void FlyingObject::kill()
{
   setAlive(false);
}

// sets the object's point to where the velocity has taken it
void FlyingObject::advance()
{
   point.addX(velocity.getDx());
   point.addY(velocity.getDy());
   stayInWorld();
}

// rotates the object by the amount passed
void FlyingObject::rotate(float rotation)
{
   this->rotation += rotation;
}

// keeps the object inside the game bounds
void FlyingObject::stayInWorld()
{
   if (point.getX() > WORLD_SIZE)
      point.setX(-WORLD_SIZE);
   if (point.getX() < -WORLD_SIZE)
      point.setX(WORLD_SIZE);
   if (point.getY() >  WORLD_SIZE)
      point.setY(-WORLD_SIZE);
   if (point.getY() < -WORLD_SIZE)
      point.setY(WORLD_SIZE);
}