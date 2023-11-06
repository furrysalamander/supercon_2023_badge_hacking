/*************************************************************
 * File: rocks.h
 * Author: Caleb Hensley
 *
 * Description: Defines the ship
 *
 * The ship will be what the user interacts with, similar to
 * the rifle of Skeet, but with additional functionality
 *************************************************************/

#ifndef ship_h
#define ship_h

#define SHIP_SIZE 7

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.05

#include "flyingObject.h"

// Put your Ship class here
class Ship : public FlyingObject
{
private:
   int rotation;
   bool thrust;
public:
   Ship();
   Ship(Point point);
   void setRotation(int rotation) { this->rotation = rotation; }
   void setThrust(bool thrust) { this->thrust = thrust; }
   int getRotation() { return rotation; }
   bool getThrust() { return thrust; }
   void rotate(int rotation);
   void launch();
   void draw();
};

#endif /* ship_h */
