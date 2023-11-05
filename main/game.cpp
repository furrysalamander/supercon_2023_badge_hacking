/*************************************************************
 * File: game.cpp
 * Author: Br. Burton with manipulation by Caleb Hensley
 *
 * Description: Contains the implementations of the
 *  method bodies for the game class.
 *
 *************************************************************/

#include "game.h"

#include "uiDraw.hpp"
#include "uiInteract.h"
#include "point.h"
#include "flyingObject.h"
#include <iostream>

#include <rtc_wdt.h>
#include <esp_task_wdt.h>


#include <vector>

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)
 : topLeft(tl), bottomRight(br)
{
   //place ship
   Point start(0, 0);
   ship = new Ship(start);
   
   // Create a vector of 5 rocks
   for (int i = 0; i < 5; i++)
   {
      Point rockStart;

      // assures that the rock doesn't spawn too close to the ship
      while (rockStart.getX() < 50 && rockStart.getX() > -50
         && rockStart.getY() < 50 && rockStart.getY() > -50)
      {
         rockStart.setX(UI::random(-WORLD_SIZE, WORLD_SIZE));
         rockStart.setY(UI::random(-WORLD_SIZE, WORLD_SIZE));
      }
      rocks.push_back(new BigRock);
      rocks[i]->setPoint(rockStart);
      rocks[i]->setRotation(BIG_ROCK_SPIN);
   }
}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
   // Delete allocated rocks
   for (int i = 0; i < rocks.size(); i++)
   {
      if (rocks[i] != NULL)
      {
         delete rocks[i];
         rocks[i] = NULL;
      }
   }
   
   // Delete allocated bullets
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i] != NULL)
      {
         delete bullets[i];
         bullets[i] = NULL;
      }
   }

   // Delete allocated ship
   if (ship != NULL)
      delete ship;
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game::advance()
{
   advanceBullets();
   advanceAsteroids();
   advanceShip();

   handleCollisions();
   cleanUpZombies();
}

/***************************************
 * GAME :: ADVANCE BULLETS
 * Go through each bullet and advance it.
 ***************************************/
void Game::advanceBullets()
{
   // Move each of the bullets forward if it is alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i]->isAlive())
      {
         //this bullet is alive, so tell it to move forward
         bullets[i]->advance();
      }
   }
}

/**************************************************************************
 * GAME :: ADVANCE ASTEROIDS
 * Advance them if they are alive and allocated
 **************************************************************************/
void Game::advanceAsteroids()
{
   for (int i = 0; i < rocks.size(); i++)
   {
      if (rocks[i] != NULL)
      {
         // we have a rock, make sure it's alive
         if (rocks[i]->isAlive())
         {
            // move it forward
            rocks[i]->advance();
         }
      }
   }

}

/**************************************************************************
 * GAME :: ADVANCE SHIP
 * Ship moves if it is alive
 **************************************************************************/
void Game::advanceShip()
{
   if (ship->isAlive())
      ship->advance();
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between a ship and each rock, and each bullet with each rock
 **************************************************************************/
void Game::handleCollisions()
{
   // If ship comes to close to a rock
   for (int i = 0; i < rocks.size(); i++)
   {
      // comparing distance of objects between frames to radius of rocks and ship
      if (getClosestDistance(*ship, *rocks[i]) < ship->getRadius() + rocks[i]->getRadius())
      {
         ship->kill();
         rocks[i]->kill();
      }
   }

   // If bullets collide with a rock
   for (int i = 0; i < bullets.size(); i++)
   {
      vector<Rock*> tempRocks;
      for (int j = 0; j < rocks.size(); j++)
      {
         // comparing distance of objects between frames to radius of rocks and bullets
         if (getClosestDistance(*bullets[i], *rocks[j]) <= bullets[i]->getRadius() + rocks[j]->getRadius())
         {
            bullets[i]->kill();
            tempRocks = rocks[j]->hit();
         }
      }
      // add the rock breakoffs to the rock vector
      rocks.insert(rocks.end(), tempRocks.begin(), tempRocks.end());
   }
}

/**************************************************************************
 * Function: getClosestDistance
 * Description: Determine how close two objects will
 *   get in between the frames.
 **************************************************************************/
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.

   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));

      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();

      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);

      distMin = min(distMin, distSquared);
   }

   return sqrt(distMin);
}

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets out of the list, take rocks out of the list)
 **************************************************************************/
void Game :: cleanUpZombies()
{
   // check for sploded rock
   vector<Rock*>::iterator rockIt = rocks.begin();
   while (rockIt != rocks.end())
   {
      Rock * pRock = *rockIt;
      if (!pRock->isAlive())
      {
         rockIt = rocks.erase(rockIt);
      }
      else
      {
         rockIt++;
      }
   }
   
   // Look for dead bullets
   vector<Bullet*>::iterator bulletIt = bullets.begin();
   while (bulletIt != bullets.end())
   {
      //Bullet bullet = *bulletIt;
      // Asteroids Hint:
      // If we had a list of pointers, we would need this line instead:
      Bullet* pBullet = *bulletIt;
      
      if (!pBullet->isAlive())
      {
         // If we had a list of pointers, we would need to delete the memory here...
         
         
         // remove from list and advance
         bulletIt = bullets.erase(bulletIt);
      }
      else
      {
         bulletIt++; // advance
      }
   }
   
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game::handleInput(const Interface & ui)
{
   // Don't do anything if the ship isn't alive
   if (!ship->isAlive()) {
      return;
   }

   // Rotate counter-clockwise
   if (ui.isLeft())
   {
      ship->rotate(ROTATE_AMOUNT);
   }
   
   // Rotate clockwise
   if (ui.isRight())
   {
      ship->rotate(-ROTATE_AMOUNT);
   }
   
   // Thrust in direction
   if (ui.isUp())
   {
      ship->setThrust(true);
      ship->launch();
   }
   else // Stop thrusting if not
   {
      ship->setThrust(false);
   }

   // shoot a bullet from ship with it's properties
   if (ui.isSpace() && /* !ui.stillSpace */ true)
   {
      Bullet * newBullet = new Bullet(ship->getPoint(), ship->getRotation(), ship->getVelocity());
      bullets.push_back(newBullet);
      // ui.stillSpace = true;
   } else { // reset bullet
      // ui.stillSpace = false;
   }

   if (ui.isEscape()) {
      this->reset(true);
   }
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw()
{
   // Draw rocks if any are alive
   for (int i = 0; i < rocks.size(); i++)
   {
      if (rocks[i]->isAlive())
      {
         rocks[i]->draw();
      }
   }
  
   // draw the ship
   if (ship->isAlive())
   {
      ship->draw();
   }
   
   // draw the bullets, if they are alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i]->isAlive())
      {
         bullets[i]->draw();
      }
   }
   
   ///this might be used if I want to put extra text on the screen
   /*
   // Put the score on the screen
   Point scoreLocation;
   scoreLocation.setX(topLeft.getX() + 5);
   scoreLocation.setY(topLeft.getY() - 5);
   
   drawNumber(scoreLocation, score);
   */
   vTaskDelay(pdMS_TO_TICKS(1000/30));
}

/*********************************************
 * GAME :: RESET
 * Sets reset flag to request a game reset
 *********************************************/
void Game :: reset(const bool b)
{
   this->resetFlag = b;
}

/*********************************************
 * GAME :: RESET REQUESTED
 * Sets reset flag to request a game reset
 *********************************************/
bool Game :: resetRequested()
{
   return this->resetFlag;
}