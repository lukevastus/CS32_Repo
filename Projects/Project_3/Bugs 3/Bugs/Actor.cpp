#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>

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
        // std::cout << "I am at " << getX() << ", " << getY() << " now." << std::endl;
        // std::cout << "I have " << sleepCounter() << " ticks of sleep remaining" << std::endl;
        setSleep(sleepCounter() - 1);
        return false;
    }
    
    return true;
}

//void Insect::bite()

void Insect::dropFood()
{
    // StudentWorld* world = getWorld();
    
}

bool Insect::eat()
{
    StudentWorld* world = getWorld();
    int amountEaten = world->consumeFood(getX(), getY(), m_hunger);
    if (amountEaten > 0)
    {
        gainHP(amountEaten);
        return true;
    }
    
    return false;
}

void Insect::move()
{
    if (getWalkCounter() == 0)
    {
        // std::cout << "I picked a new direction" << std::endl;
        newDir();
        int distance = randInt(2, 10);
        setWalkCounter(distance);
    }
    
    StudentWorld* world = getWorld();
    int newX = getX();
    int newY = getY();
    
    switch (getDirection())
    {
        case up:
            newY++;
            break;
        case right:
            newX++;
            break;
        case down:
            newY--;
            break;
        case left:
            newX--;
            break;
        default:
            break;
    }
    
    // std::cout << "I attempt to move from" << getX() << ", " << getY() << " to " << newX << ", " << newY << std::endl;
    
    if (world->isBlocked(newX, newY))
    {
        // std::cout << "I am blocked" << std::endl;
        setWalkCounter(0);
        return;
    }
    
    world->moveActor(getX(), getY(), newX, newY, this);
    moveTo(newX, newY);
    setWalkCounter(getWalkCounter() - 1);
    // std::cout << "I moved" << std::endl;
}

void Insect::newDir()
{
    int dir = randInt(1, 4);
    switch (dir)
    {
        case 1:
            setDirection(up);
            break;
        case 2:
            setDirection(right);
            break;
        case 3:
            setDirection(down);
            break;
        case 4:
            setDirection(left);
            break;
        default:
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Baby grasshopper class

void BabyGrasshopper::doSomething()
{
    // std::cout << "I am prompted to do something" << std::endl;
    if (!attemptAct())
        return;

    if (doGrasshopperThings())
    {
        if (isDead())
            return;
        
        int rest = 0;
        if (eat())
            rest = randInt(0, 1);
        
        if (!rest)
            move();
    }
    
    setSleep(2);
}

bool BabyGrasshopper::doGrasshopperThings()
{
    /*if (getHP() >= 1600)
    {
        // mature();
        // Actor* adult = new Grasshopper:
        Actor* adult = nullptr;
        getWorld()->addActor(getX(), getY(), adult);
        loseHP(getHP());
        dropFood();
        return 0;
    }*/
    
    return 1;
}

// void BabyGrasshopper::mature()

