/*************************************************************
 * File: bullet.cpp
 * Author: Caleb Hensley
 *
 * Description: Contains the implementations of the
 *  method bodies for the Bullet class
 *************************************************************/

#include "bullet.h"
#include <cmath>
#include <iostream>
using namespace std;


// default constructor
Bullet::Bullet()
{
   setRadius(1);
   ttl = 40;
}

// non-default
Bullet::Bullet(Point shipPoint, float angle, Velocity shipVel)
{
   // calls the fire method, giving game less to do and know
   fire(shipPoint, angle, shipVel);
   setRadius(1);
   ttl = 40;
}

// calls the uiDraw function to draw a bullet
void Bullet::draw()
{
   UI::drawDot(point);
   if (!ttl--)
      kill();
}

// fires a bullet from a passed in point and angle 
void Bullet::fire(Point point, float angle, Velocity shipVel)
{
   setPoint(point);

   // sets the bullet speed at the angle of the ship + the velocity of the ship
   velocity.setDx(shipVel.getDx() + BULLET_SPEED * (-sin(M_PI / 180.0 * angle)));
   velocity.setDy(shipVel.getDy() + BULLET_SPEED * (cos(M_PI / 180.0 * angle)));
}
