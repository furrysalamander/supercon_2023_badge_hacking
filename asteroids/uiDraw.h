/***********************************************************************
 * Header File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#ifndef UI_DRAW_H
#define UI_DRAW_H

#include <string>     // To display text on the screen
#include <cmath>      // for M_PI, sin() and cos()
#include "point.h"    // Where things are drawn
using std::string;

// ultra simple point
struct PT
{
   int x;
   int y;
};

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *************************************************************************/
void rotate(Point & point, const Point & origin, int rotation = 0);

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void drawLine(const Point & begin, const Point & end,
             float red = 1.0, float green = 1.0, float blue = 1.0);

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *************************************************************************/
void drawDot(const Point & point);

/************************************************************************      
 * DRAW Ship                                                                   
 * Draw the spaceship on the screen                                         
 *************************************************************************/
void drawShip(const Point & point, int rotation, bool thrust = false);

/************************************************************************
 * DRAW X-Wing
 * Draw an X-Wing on the screen
 *************************************************************************/
void drawXwing(const Point & point, int rotation, bool thrust = false);

/**********************************************************************
 * DRAW * ASTEROID
 **********************************************************************/
void drawSmallAsteroid( const Point & point, int rotation);
void drawMediumAsteroid(const Point & point, int rotation);
void drawLargeAsteroid( const Point & point, int rotation);

/******************************************************************
 * RANDOM
 * This function generates a random number.  The user specifies
 * The parameters 
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int    random(int    min, int    max);
double random(double min, double max);


#endif // UI_DRAW_H
