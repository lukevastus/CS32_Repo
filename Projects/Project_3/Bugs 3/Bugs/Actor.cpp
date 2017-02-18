#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Insect class

bool Insect::attemptAct()
{
    loseHP(1);
    
    if (Actor::isDead())
    {
        dropFood();
        return false;
    }
    
    if (sleepCounter() > 0)
    {
        setSleep(sleepCounter() - 1);
        return false;
    }
    
    return true;
}

//void Insect::bite()

//void Insect::eat()

void Insect::dropFood()
{
    StudentWorld* world = Actor::getWorld();
    
}

void Insect::move()
{
    
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Baby grasshopper class
void BabyGrasshopper::doSomething()
{
    if (Insect::attemptAct())
    {
    
    }
}