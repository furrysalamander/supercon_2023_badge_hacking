/*************************************************************
 * File: game.h
 * Author: Br. Burton & Caleb Hensley
 *
 * Description: The game of Asteroids. Much of this was copied
 *  from the previous skeet game. Much is different for
 *  asteroids. This class holds each piece of the game.
 *  It also has methods that make the game happen (advance,
  * interact, etc.)
 *************************************************************/

#ifndef GAME_H
#define GAME_H

#define WORLD_SIZE 300

#include <vector>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "flyingObject.h"
#include "rocks.h"
#include "ship.h"
#include "bullet.h"

/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
   /*********************************************
    * Constructor
    * Initializes the game
    *********************************************/
   Game(Point tl, Point br);
   ~Game();
   
   /*********************************************
    * Function: handleInput
    * Description: Takes actions according to whatever
    *  keys the user has pressed.
    *********************************************/
   void handleInput(const Interface & ui);
   
   /*********************************************
    * Function: advance
    * Description: Move everything forward one
    *  step in time.
    *********************************************/
   void advance();
   
   /*********************************************
    * Function: draw
    * Description: draws everything for the game.
    *********************************************/
   void draw(const Interface & ui);

   /*********************************************
    * Function: reset
    * Description: Resets the game
    *********************************************/
   void reset(const bool b);
   
   /*********************************************
    * Function: shouldReset
    * Description: Checks whether game should be
    * reset
    *********************************************/
   bool resetRequested();
   
private:
   // If set, indicates that the next attempt to advance should reset the game
   bool resetFlag = true;

   // The coordinates of the screen
   Point topLeft;
   Point bottomRight;
   
   //int score; (may be used later)
   
   Ship * ship;
   std::vector<Bullet*> bullets;
   
   // TODO: declare your vector of rocks here
   std::vector<Rock*> rocks;

   /*************************************************
    * Private methods to help with the game logic.
    *************************************************/
   void advanceBullets();
   void advanceAsteroids();
   void advanceShip();
   void handleCollisions();
   void cleanUpZombies();

   float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;
};

#endif /* GAME_H */
