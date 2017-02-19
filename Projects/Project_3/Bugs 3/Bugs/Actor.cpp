#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Insect class

bool Insect::attemptAct()
{
    loseHP(1);
    
    if (isDead())
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
    StudentWorld* world = getWorld();
    
}

void Insect::move()
{
    StudentWorld* world = getWorld();
    
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Baby grasshopper class
void BabyGrasshopper::doSomething()
{
    bool canMove = attemptAct();
    if (!canMove)
    {
        return;
    }
    
    
}