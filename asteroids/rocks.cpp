#include "rocks.h"

/*************************
* Big Rock
**************************/

// default constructor for rock
BigRock::BigRock()
{
   radius = BIG_ROCK_SIZE;
   setAngle(random(0, 360));
   velocity.setDx(ROCK_SPEED * (-sin(M_PI / 180.0 * getAngle())));
   velocity.setDy(ROCK_SPEED * (cos(M_PI / 180.0 * getAngle())));
}

// returns 2 medium, and 1 small rocks if hit, with added velocity
vector<Rock*> BigRock::hit()
{
   kill();
   vector<Rock*> tempRocks;
   Velocity mediumVelocity(getVelocity());
   mediumVelocity.setDx(mediumVelocity.getDx() - 1);
   tempRocks.push_back(new MediumRock(getPoint(), getAngle(), mediumVelocity));

   mediumVelocity.setDx(mediumVelocity.getDx() - 1);
   tempRocks.push_back(new MediumRock(getPoint(), getAngle(), mediumVelocity));

   Velocity smallVelocity(getVelocity());
   smallVelocity.setDx(smallVelocity.getDy() + 2);
   tempRocks.push_back(new SmallRock(getPoint(), getAngle(), getVelocity()));

   return tempRocks;
}

// draws a large rock with appropriate rotation
void BigRock::draw()
{
   radius = BIG_ROCK_SIZE;
   drawLargeAsteroid(point, rotation);
   rotation += BIG_ROCK_SPIN;
}

/*************************
* Medium Rock
**************************/
MediumRock::MediumRock(Point point, int angle, Velocity velocity)
{
   radius = MEDIUM_ROCK_SIZE;
   setPoint(point);
   this->setAngle(angle);
   setVelocity(velocity);
}

// returns 2 small rocks if hit, with added velocity
vector<Rock*> MediumRock::hit()
{
   kill();
   vector<Rock*> tempRocks;
   Velocity smallVelocity(getVelocity());
   smallVelocity.setDy(smallVelocity.getDy() + 3);
   tempRocks.push_back(new SmallRock(getPoint(), (getAngle() + 90), smallVelocity));

   smallVelocity.setDy(smallVelocity.getDy() - 6);
   tempRocks.push_back(new SmallRock(getPoint(), (getAngle() - 90), getVelocity()));
   return tempRocks;
}

// draws a medium rock with appropriate rotation
void MediumRock::draw()
{
   rotation += MEDIUM_ROCK_SPIN;
   drawMediumAsteroid(point, rotation);
}

/*************************
* Small Rock
**************************/
// non-default constructor for medium rock, takes properties of previous rock
SmallRock::SmallRock(Point point, int angle, Velocity velocity)
{
   radius = SMALL_ROCK_SIZE;
   setPoint(point);
   this->setAngle(angle);
   setVelocity(velocity);
}

// returns an empty vector of rock pointers if hit
vector<Rock*> SmallRock::hit()
{
   kill();
   vector<Rock*> tempRocks;
   return tempRocks;
}

// draws a small rock with appropriate rotation
void SmallRock::draw()
{
   rotation += SMALL_ROCK_SPIN;
   drawSmallAsteroid(point, rotation);
}