#include "ship.h"

#define M_PI 3.141

// Put your ship methods here
Ship::Ship()
{
   rotation = 0;
   thrust = false;
   radius = SHIP_SIZE;
}

Ship::Ship(Point point)
{
   this->point = point;
   rotation = 0;
   thrust = false;
   radius = SHIP_SIZE;
}

void Ship::draw()
{
   drawShip(point, rotation, thrust);
   // drawXwing(point, rotation, thrust);
}

void Ship::rotate(int rotation)
{
   setRotation(this->rotation += rotation);
   this->rotation == 360 || this->rotation == -360 ? this->rotation = 0 : NULL;
}

void Ship::launch()
{
   velocity.setDx(velocity.getDx() + (THRUST_AMOUNT * (-sin(M_PI / 180.0 * rotation))));
   velocity.setDy(velocity.getDy() + (THRUST_AMOUNT * (cos(M_PI / 180.0 * rotation))));
}