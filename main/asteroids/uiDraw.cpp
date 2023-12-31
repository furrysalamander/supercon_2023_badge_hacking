/***********************************************************************
 * Source File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock

#include "point.h"
#include "uiDraw.h"

using namespace std;

#define deg2rad(value) ((M_PI / 180) * (value))


/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  point    The point to be moved
 *           center   The center point we will rotate around
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
void rotate(Point & point, const Point & origin, int rotation)
{
   // because sine and cosine are expensive, we want to call them only once
   double cosA = cos(deg2rad(rotation));
   double sinA = sin(deg2rad(rotation));

   // remember our original point
   Point tmp(false /*check*/);
   tmp.setX(point.getX() - origin.getX());
   tmp.setY(point.getY() - origin.getY());

   // find the new values
   point.setX(static_cast<int> (tmp.getX() * cosA -
                                tmp.getY() * sinA) +
              origin.getX());
   point.setY(static_cast<int> (tmp.getX() * sinA +
                                tmp.getY() * cosA) +
              origin.getY());
}

/******************************************************************
 * RANDOM
 * This function generates a random number.  
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int random(int min, int max)
{
   assert(min < max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);

   return num;
}

/******************************************************************
 * RANDOM
 * This function generates a random number.  
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the double
 ****************************************************************/
double random(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   
   assert(min <= num && num <= max);

   return num;
}

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *  INPUT point   The position of the dow
 *************************************************************************/
void drawDot(const Point & point)
{
   auto x = point.getX();
   auto y = point.getY();

   Point points[] = {
      {x,       y},
      {x + 1,   y},
      {x + 1,   y},
      {x,       y}
   };
   // TODO: insert points
}

/**********************************************************************
 * DRAW SMALL ASTEROID
 **********************************************************************/
void drawSmallAsteroid( const Point & center, int rotation)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   } points[] = 
   {
      {-5, 9},  {4, 8},   {8, 4},   
      {8, -5},  {-2, -8}, {-2, -3}, 
      {-8, -4}, {-8, 4},  {-5, 10}
   };
   
   for (int i = 0; i < sizeof(points)/sizeof(PT); i++)
   {
      Point pt(center.getX() + points[i].x, 
               center.getY() + points[i].y);
      rotate(pt, center, rotation);
      // TODO: insert pt
   }
}

/**********************************************************************
 * DRAW MEDIUM ASTEROID
 **********************************************************************/
void drawMediumAsteroid( const Point & center, int rotation)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   } points[] = 
   {
      {2, 8},    {8, 15},    {12, 8}, 
      {6, 2},    {12, -6},   {2, -15},
      {-6, -15}, {-14, -10}, {-15, 0},
      {-4, 15},  {2, 8}
   };
   
   for (int i = 0; i < sizeof(points)/sizeof(PT); i++)
   {
      Point pt(center.getX() + points[i].x, 
               center.getY() + points[i].y);
      rotate(pt, center, rotation);
      // TODO: insert pt
   }
}

/**********************************************************************
 * DRAW LARGE ASTEROID
 **********************************************************************/
void drawLargeAsteroid( const Point & center, int rotation)
{
   // ultra simple point
   const PT points[] = 
   {
      {0, 12},    {8, 20}, {16, 14},
      {10, 12},   {20, 0}, {0, -20},
      {-18, -10}, {-20, -2}, {-20, 14},
      {-10, 20},  {0, 12}
   };
   
   for (int i = 0; i < sizeof(points)/sizeof(PT); i++)
   {
      Point pt(center.getX() + points[i].x, 
               center.getY() + points[i].y);
      rotate(pt, center, rotation);
      // TODO: insert pt
   }
}

void drawFlame(const Point & center, int rotation)
{
   const PT pointsFlame[3][5] =
   {
      { {-2, -3}, {-2, -13}, { 0, -6}, { 2, -13}, {2, -3} },
      { {-2, -3}, {-4,  -9}, {-1, -7}, { 1, -14}, {2, -3} },
      { {-2, -3}, {-1, -14}, { 1, -7}, { 4,  -9}, {2, -3} }
   };
   
   int iFlame = random(0, 3);
   for (int i = 0; i < 5; i++)
   {
      Point pt(center.getX() + pointsFlame[iFlame][i].x, 
               center.getY() + pointsFlame[iFlame][i].y);
      rotate(pt, center, rotation);
      // TODO: insert pt into list
   }
}


/************************************************************************       
 * DRAW Ship                                                                    
 * Draw a spaceship on the screen                                               
 *  INPUT point   The position of the ship                                      
 *        angle   Which direction it is ponted                                  
 *************************************************************************/
void drawShip(const Point & center, int rotation, bool thrust)
{
   
   // draw the ship                                                 
   const PT pointsShip[] = 
   { // top   r.wing   r.engine l.engine  l.wing    top
      {0, 6}, {6, -6}, {2, -3}, {-2, -3}, {-6, -6}, {0, 6}  
   };
   
   for (int i = 0; i < sizeof(pointsShip)/sizeof(PT); i++)
   {
      Point pt(center.getX() + pointsShip[i].x, 
               center.getY() + pointsShip[i].y);
      rotate(pt, center, rotation);
      // TODO: insert pt into list
   }

   // draw the flame if necessary
   if (thrust)
   {
      drawFlame(center, rotation);
   }
}

/************************************************************************
 * DRAW X-Wing
 * Draw an X-Wing on the screen
 *  INPUT point   The position of the ship
 *        angle   Which direction it is ponted
 *************************************************************************/
void drawXwing(const Point & center, int rotation, bool thrust)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   };

   const PT pointsShip[] =
   { // tip >  < right wing  >  < right shooter >  <end right wing>
      {0, 16}, {3, 0}, {10, 0}, {10, 8}, {10, -4}, {7, -4}, {7, -6}, {0, -5},
      {-7, -6}, {-7, -4}, {-10, -4}, {-10, 8}, {-10, 0}, {-3, 0}, {0, 16}
   };

   for (int i = 0; i < sizeof(pointsShip) / sizeof(PT); i++)
   {
      Point pt(center.getX() + pointsShip[i].x,
         center.getY() + pointsShip[i].y);
      rotate(pt, center, rotation);
      // TODO: insert pt into list
   }

   // draw the flame if necessary
   if (thrust)
   {
      drawFlame(center, rotation);
   }
}