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
#include <vector>

#include "uiDraw.hpp"

#include "rasterize.hpp"

using namespace std;

#define deg2rad(value) ((M_PI / 180.0f) * (value))

std::vector<Shape> UI::scene = std::vector<Shape>();

const float UI::VECTORSCOPE_SCALE = 0.007;
const float UI::VECTORSCOPE_ROTATION = -90;

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  point    The point to be moved
 *           center   The center point we will rotate around
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
void UI::rotate(Point & point, const Point & origin, int rotation)
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
int UI::random(int min, int max)
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
double UI::random(double min, double max)
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
void UI::drawDot(const Point & point)
{
   auto x = point.getX();
   auto y = point.getY();

   const auto dot = Shape {
      {
         x,       y,
         x + 1,   y,
         x + 1,   y,
         x,       y
      }
   };

   UI::scene.push_back(dot);
}

/**********************************************************************
 * DRAW SMALL ASTEROID
 **********************************************************************/
void UI::drawSmallAsteroid( const Point & center, int rotation)
{
   // ultra simple point
   const auto asteroid = Shape 
   {
      {
         -5, 9,  4, 8,   8, 4,   
         8, -5,  -2, -8, -2, -3, 
         -8, -4, -8, 4,  -5, 10
      }
   };

   UI::scene.push_back(asteroid);
   UI::scene.back().rotate(deg2rad(rotation));
   UI::scene.back().translate(center.getX(), center.getY());
}

/**********************************************************************
 * DRAW MEDIUM ASTEROID
 **********************************************************************/
void UI::drawMediumAsteroid( const Point & center, int rotation)
{
   // ultra simple point
   const auto asteroid = Shape {
      {
         2, 8,    8, 15,    12, 8, 
         6, 2,    12, -6,   2, -15,
         -6, -15, -14, -10, -15, 0,
         -4, 15,  2, 8
      }
   };

   UI::scene.push_back(asteroid);
   UI::scene.back().rotate(deg2rad(rotation));
   UI::scene.back().translate(center.getX(), center.getY());
}

/**********************************************************************
 * DRAW LARGE ASTEROID
 **********************************************************************/
void UI::drawLargeAsteroid( const Point & center, int rotation)
{
   // ultra simple point
   const auto asteroid = Shape {
      {
         0, 12,    8, 20, 16, 14,
         10, 12,   20, 0, 0, -20,
         -18, -10, -20, -2, -20, 14,
         -10, 20,  0, 1
      }
   };
   
   UI::scene.push_back(asteroid);
   UI::scene.back().rotate(deg2rad(rotation));
   UI::scene.back().translate(center.getX(), center.getY());
}

// ORIGINAL
// void UI::drawFlame(const Point & center, int rotation)
// {
//    const UI::PT pointsFlame[3][5] =
//    {
//       { {-2, -3}, {-2, -13}, { 0, -6}, { 2, -13}, {2, -3} },
//       { {-2, -3}, {-4,  -9}, {-1, -7}, { 1, -14}, {2, -3} },
//       { {-2, -3}, {-1, -14}, { 1, -7}, { 4,  -9}, {2, -3} }
//    };
   
//    int iFlame = UI::random(0, 3);
//    for (int i = 0; i < 5; i++)
//    {
//       Point pt(center.getX() + pointsFlame[iFlame][i].x, 
//                center.getY() + pointsFlame[iFlame][i].y);
//       rotate(pt, center, rotation);
//       // TODO: insert pt into list
//    }
// }

void UI::drawFlame(const Point & center, int rotation)
{
   const vector<float> pointsFlame[] =
   {
      { -2.0f, -3.0f, -2.0f, -13.0f, 0.0f, -6.0f,  2.0f, -13.0f, 2.0f, -3.0f },
      { -2.0f, -3.0f, -4.0f, -9.0f, -1.0f, -7.0f, 1.0f, -14.0f, 2.0f, -3.0f },
      { -2.0f, -3.0f, -1.0f, -14.0f, 1.0f, -7.0f, 4.0f,  -9.0f, 2.0f, -3.0f }
   };
   
   int iFlame = UI::random(0, 3);
   UI::scene.emplace_back(pointsFlame[iFlame]);
   UI::scene.back().rotate(deg2rad(rotation));
   UI::scene.back().translate(center.getX(), center.getY());
}

/************************************************************************       
 * DRAW Ship                                                                    
 * Draw a spaceship on the screen                                               
 *  INPUT point   The position of the ship                                      
 *        angle   Which direction it is ponted                                  
 *************************************************************************/
void UI::drawShip(const Point & center, int rotation, bool thrust)
{
   
   // draw the ship                                                 
   const auto ship = Shape {
      { // top   r.wing   r.engine l.engine  l.wing    top
         0, 6, 6, -6, 2, -3, -2, -3, -6, -6, 0, 6 
      }
   };

   UI::scene.push_back(ship);
   UI::scene.back().rotate(deg2rad(rotation));
   UI::scene.back().translate(center.getX(), center.getY());
   
   // draw the flame if necessary
   if (thrust)
   {
      UI::drawFlame(center, rotation);
   }
}

/************************************************************************
 * DRAW X-Wing
 * Draw an X-Wing on the screen
 *  INPUT point   The position of the ship
 *        angle   Which direction it is ponted
 *************************************************************************/
void UI::drawXwing(const Point & center, int rotation, bool thrust)
{
   const auto xwing = Shape {
   // tip >  < right wing  >  < right shooter >  <end right wing>
      {
         0, 16, 3, 0, 10, 0, 10, 8, 10, -4, 7, -4, 7, -6, 0, -5,
         -7, -6, -7, -4, -10, -4, -10, 8, -10, 0, -3, 0, 0, 16
      }
   };

   // draw the flame if necessary
   if (thrust)
   {
      UI::drawFlame(center, rotation);
   }

   UI::scene.push_back(xwing);
   UI::scene.back().rotate(deg2rad(rotation));
   UI::scene.back().translate(center.getX(), center.getY());
}

/******************************************************************
 * DISPLAY
 * Renders screen buffer to the screen
 ****************************************************************/
void UI::display() {
   for(auto& object : UI::scene) {
      object.scale(VECTORSCOPE_SCALE, VECTORSCOPE_SCALE);
   }
   auto output_coords = rasterize(UI::scene);

   dac::update_buffer(std::move(output_coords));
   UI::scene.clear();
}

/******************************************************************
 * INIT
 * Renders screen buffer to the screen
 *****************************************************************/
void UI::init() {
   dac::init_oneshot_dac();
}