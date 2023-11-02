/*************************************************************
 * Header File:
 *    VELOCITY : A class controlling the velocity of the lander
 * Author:
 *    Caleb Hensley
 * Summary:
 *    I used this for the moonLander project, it holds and
 *    modifies velocity information for any moving object
 *************************************************************/

#ifndef VELOCITY_H
#define VELOCITY_H

 /*********************************************
  * VELOCITY
  * holds velocity information for an object and
  * allows it to be set and read.
  *********************************************/
class Velocity
{
private:
	float x;
	float y;
public:
	Velocity();
	Velocity(const float x, const float y);
	float getDx();
	float getDy();
	void setDx(const float x);
	void setDy(const float y);
};

#endif