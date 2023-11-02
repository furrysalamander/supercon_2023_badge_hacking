/*************************************************************
 * File: velocity.cpp
 * Author: Caleb Hensley
 *
 * Description: Contains the implementations of the
 *  method bodies for the Velocity class
 *
 *************************************************************/

#include "velocity.h"
#include <iostream>
using namespace std;

// initializes velocity to 0
Velocity::Velocity()
{
	x = 0.0;
	y = 0.0;
}

// initializes velocity to whatever the user wants
Velocity::Velocity(const float x, const float y)
{
	this->x = x;
	this->y = y;
}

// returns current velocity for x
float Velocity::getDx()
{
	return x;
}

// returns current velocity for y
float Velocity::getDy()
{
	return y;
}

// sets x velocity to user input
void Velocity::setDx(const float x)
{
   this->x = x;
}

// sets y velocity to user input
void Velocity::setDy(const float y)
{
   this->y = y;
}
