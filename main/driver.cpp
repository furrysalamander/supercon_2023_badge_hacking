/*****************************************************
 * Driver.cpp
 *
 * This file contains the main function
 *  that starts the game and the callback function
 *  that specifies what methods of the game class are
 *  called each time through the game loop.
 ******************************************************/
#include "game.h"
#include "uiInteract.h"


/*************************************
 * All the interesting work happens here, when OpenGL
 * calls this to draw a frame. When it's finished,
 * the graphics engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
   Game *pGame = (Game *)p;

   pGame->advance();
   pGame->handleInput(*pUI);
   pGame->draw();
}


/*********************************
 * Main is pretty sparse.  Just initialize
 * the game and call the display engine.
 *********************************/
int main(int argc, char ** argv)
{
   Point topLeft(-WORLD_SIZE, WORLD_SIZE);
   Point bottomRight(WORLD_SIZE, -WORLD_SIZE);
   Game game(topLeft, bottomRight);

   Interface ui("Asteroids", topLeft, bottomRight);
   ui.run(callBack, &game);
   
   return 0;
}
