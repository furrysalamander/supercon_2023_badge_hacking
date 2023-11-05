/***********************************************************************
 * Source File:
 *     UI INTERACT
 * Author:
 *     Br. Helfrich
 * Description:
 *     Implement the interfaces specified in uiInterface.h.  This handles
 *     all the interfaces and events necessary to work with OpenGL.  Your
 *     program will interface with this thorough the callback function
 *     pointer towards the bottom of the file.
 ************************************************************************/

#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock
#include <cstdlib>    // for rand()
#include <driver/gpio.h>

#include <rtc_wdt.h>
#include <esp_task_wdt.h>

#include "uiInteract.h"
#include "point.h"

using namespace std;


/*********************************************************************
 * SLEEP
 * Pause for a while.  We want to put the program to sleep until it
 * is time to draw again.  Note that this requires us to tell the OS
 * that we are idle.  the nanosleep function performs this task for us
 *   INPUT: msSleep: sleep time in milliseconds
 *********************************************************************/
void sleep(unsigned long msSleep)
{
   // TODO: find esp32 sleep
   
   vTaskDelay(pdMS_TO_TICKS(msSleep));
   return;
}

/************************************************************************
 * DRAW CALLBACK
 * This is the main callback from OpenGL. It gets called constantly by
 * the graphics engine to refresh and draw the window.  Here we will
 * clear the background buffer, draw on it, and send it to the forefront
 * when the appropriate time period has passsed.
 *
 * Note: This and all other callbacks can't be member functions, they must
 * have global scope for OpenGL to see them.
 *************************************************************************/
void drawCallback()
{
   // even though this is a local variable, all the members are static
   Interface ui;
   // Prepare the background buffer for drawing
   // TODO: clear the screen? Maybe I don't need to

   //calls the client's display function
   assert(ui.callBack != NULL);
   ui.callBack(&ui, ui.p);
   
   //loop until the timer runs out
   if (!ui.isTimeToDraw())
      sleep((unsigned long)((ui.getNextTick() - clock()) / 1000));

   // from this point, set the next draw time
   ui.setNextDrawTime();

   // bring forth the background buffer
   // glutSwapBuffers();

   // TODO: Write buffer out?

   // clear the space at the end
   ui.keyEvent();
}

/************************************************************************
 * KEY DOWN CALLBACK
 * When a key on the keyboard has been pressed, we need to pass that
 * on to the client.  Currently, we are only registering the arrow keys
 *   INPUT   key:   the key we pressed according to the GLUT_KEY_ prefix
 *           x y:   the position in the window, which we ignore
 *************************************************************************/
void keyDownCallback(Button button, int x, int y)
{
   // Even though this is a local variable, all the members are static
   // so we are actually getting the same version as in the constructor.
   Interface ui;
   ui.keyEvent(button, true /*fDown*/);
}

/************************************************************************
 * KEY UP CALLBACK
 * When the user has released the key, we need to reset the pressed flag
 *   INPUT   key:   the key we pressed according to the GLUT_KEY_ prefix
 *           x y:   the position in the window, which we ignore
 *************************************************************************/
void keyUpCallback(Button button, int x, int y)
{
   // Even though this is a local variable, all the members are static
   // so we are actually getting the same version as in the constructor.
   Interface ui;
   ui.keyEvent(button, false /*fDown*/);
}

/***************************************************************
 * KEYBOARD CALLBACK
 * Generic callback to a regular ascii keyboard event, such as
 * the space bar or the letter 'q'
 ***************************************************************/
void keyboardCallback(Button button, int x, int y)
{
   // Even though this is a local variable, all the members are static
   // so we are actually getting the same version as in the constructor.
   Interface ui;
   ui.keyEvent(button, true /*fDown*/);
}

void checkButtons() {  
   Interface::isLeftPress = (int)!gpio_get_level(GPIO_LEFT);
   Interface::isRightPress = (int)!gpio_get_level(GPIO_RIGHT);
   Interface::isSpacePress = (int)!gpio_get_level(GPIO_SHOOT);
   Interface::isUpPress = (int)!gpio_get_level(GPIO_FORWARD);

   std::printf("%d, %d, %d, %d\n", Interface::isLeftPress, Interface::isRightPress, Interface::isSpacePress, Interface::isUpPress);
}

/***************************************************************
 * INTERFACE : KEY EVENT
 * Either set the up or down event for a given key
 *   INPUT   key     which key is pressed
 *           fDown   down or brown
 ****************************************************************/
void Interface::keyEvent(Button button, bool fDown)
{
   switch(button)
   {
      case STICK_UP:
         isDownPress = fDown;
         break;
      case STICK_DOWN:
         isUpPress = fDown;
         break;
      case STICK_RIGHT:
         isRightPress = fDown;
         break;
      case STICK_LEFT:
         isLeftPress = fDown;
         break;
      case LEVEL:
         isUpPress = fDown;
         break;
      case RANGE:
         isSpacePress = fDown;
         break;
   }
}

/***************************************************************
 * INTERFACE : KEY EVENT
 * Either set the up or down event for a given key
 *   INPUT   key     which key is pressed
 *           fDown   down or brown
 ****************************************************************/
void Interface::keyEvent()
{
   if (isDownPress)
      isDownPress++;
   if (isUpPress)
      isUpPress++;
   if (isLeftPress)
      isLeftPress++;
   if (isRightPress)
      isRightPress++;
   isSpacePress = false;
}


/************************************************************************
 * INTEFACE : IS TIME TO DRAW
 * Have we waited long enough to draw swap the background buffer with
 * the foreground buffer?
 *************************************************************************/
bool Interface::isTimeToDraw()
{
   return ((unsigned int)clock() >= nextTick);
}

/************************************************************************
 * INTERFACE : SET NEXT DRAW TIME
 * What time should we draw the buffer again?  This is a function of
 * the current time and the frames per second.
 *************************************************************************/
void Interface::setNextDrawTime()
{
   nextTick = clock() + static_cast<int> (timePeriod * CLOCKS_PER_SEC);
}

/************************************************************************
 * INTERFACE : SET FRAMES PER SECOND
 * The frames per second dictates the speed of the game.  The more frames
 * per second, the quicker the game will appear to the user.  We will default
 * to 30 frames/second but the client can set this at will.
 *    INPUT  value        The number of frames per second.  30 is default
 *************************************************************************/
void Interface::setFramesPerSecond(float value)
{
    timePeriod = (1 / value);
}

/***************************************************
 * STATICS
 * All the static member variables need to be initialized
 * Somewhere globally.  This is a good spot
 **************************************************/
int          Interface::isDownPress   = 0;
int          Interface::isUpPress     = 0;
int          Interface::isLeftPress   = 0;
int          Interface::isRightPress  = 0;
bool         Interface::isEscapePress = false;
bool         Interface::isSpacePress  = false;
bool         Interface::stillSpace    = false;
bool         Interface::initialized   = false;
double       Interface::timePeriod    = 1.0 / 30; // default to 30 frames/second
unsigned int Interface::nextTick      = 0;        // redraw now please
void *       Interface::p             = NULL;
void (*Interface::callBack)(const Interface *, void *) = NULL;


/************************************************************************
 * INTERFACE : DESTRUCTOR
 * Nothing here!
 ***********************************************************************/
Interface::~Interface()
{
}


/************************************************************************
 * INTEFACE : INITIALIZE
 * Initialize our drawing window.  This will set the size and position,
 * get ready for drawing, set up the colors, and everything else ready to
 * draw the window.  All these are part of initializing Open GL.
 *  INPUT    argc:       Count of command-line arguments from main
 *           argv:       The actual command-line parameters
 *           title:      The text for the titlebar of the window
 *************************************************************************/
void Interface::initialize(const char * title, Point topLeft, Point bottomRight)
{
   if (initialized)
      return;
   
   // set up the random number generator
   // srand((unsigned int)time(NULL));

   // // create the window
   // glutInit(&argc, argv);
   // Point point;
   // glutInitWindowSize(   // size of the window
   //    (int)(bottomRight.getX() - topLeft.getX()),
   //    (int)(topLeft.getY() - bottomRight.getY()));
            
   // glutInitWindowPosition( 10, 10);                // initial position 
   // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // double buffering
   // glutCreateWindow(title);              // text on titlebar
   // glutIgnoreKeyRepeat(true);
   
   // // set up the drawing style: B/W and 2D
   // glClearColor(0, 0, 0, 0);          // Black is the background color
   // gluOrtho2D((int)topLeft.getX(), (int)bottomRight.getX(),
   //            (int)bottomRight.getY(), (int)topLeft.getY()); // 2D environment

   // // register the callbacks so OpenGL knows how to call us
   // glutDisplayFunc(   drawCallback    );
   // glutIdleFunc(      drawCallback    );
   // glutKeyboardFunc(  keyboardCallback);
   // glutSpecialFunc(   keyDownCallback );
   // glutSpecialUpFunc( keyUpCallback   );
   
   // TODO: what to do here instead?

   initialized = true;
   
   // done
   return;
}

/************************************************************************
 * INTERFACE : RUN
 *            Start the main graphics loop and play the game
 * INPUT callBack:   Callback function.  Every time we are beginning
 *                   to draw a new frame, we first callback to the client
 *                   to see if he wants to do anything, such as move
 *                   the game pieces or respond to input
 *       p:          Void point to whatever the caller wants.  You
 *                   will need to cast this back to your own data
 *                   type before using it.
 *************************************************************************/
void Interface::run(void (*callBack)(const Interface *, void *), void *p)
{
   // setup the callbacks
   this->p = p;
   this->callBack = callBack;

   // TODO: Replace glutmainloop with new interface updating loop
   // glutMainLoop();

   return;
}

