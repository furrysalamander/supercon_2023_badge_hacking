/*************************************************************
 * File: rocks.h
 * Author: Caleb Hensley
 *
 * Description: Defines all rocks
 *
 * There is a rock base class and three derived rocks,
 * Big, Medium, and Small
 *************************************************************/

#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#define ROCK_SPEED 1

#include "flyingObject.h"


// Define the following classes here:
//   Rock Base class
class Rock : public FlyingObject
{
private:
   int angle;
public:
   int getAngle() { return angle;}
   void setAngle(int angle) { this->angle = angle; }
   virtual vector<Rock*> hit() = 0;
   virtual void draw() = 0;
   virtual ~Rock() = default;
};

//   BigRock
class BigRock : public Rock
{
public:
   BigRock();
   vector<Rock*> hit();
   void draw();
};

//   MediumRock
class MediumRock : public Rock
{
public:
   MediumRock(Point, int, Velocity);
   vector<Rock*> hit();
   void draw();
};

//   SmallRock
class SmallRock : public Rock
{
public:
   SmallRock(Point, int, Velocity);
   vector<Rock*> hit();
   void draw();
};

#endif /* rocks_h */
