#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
#include <cmath>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Actor class

void Actor::loseHP(int num)
{
    m_hp = m_hp > num ? (m_hp - num) : 0;
    if (isDead())
        dropFood(m_drop);
}

void Actor::dropFood(int amount)
{
    if (amount > 0)
        m_world->stackFood(getX(), getY(), amount);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Pool of Water class

void PoolofWater::doSomething()
{
    StudentWorld* world = getWorld();
    world->stunAOE(getX(), getY(), 2);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Poison class

void Poison::doSomething()
{
    StudentWorld* world = getWorld();
    world->damageAOE(getX(), getY(), 150);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Insect class

bool Insect::attemptAct()
{
    loseHP(1);
    
    if (isDead())
    {
        return false;
    }
    
    if (sleepCounter() > 0)
    {
        // std::cout << "I am at " << getX() << ", " << getY() << " now." << std::endl;
        // std::cout << "I have " << sleepCounter() << " ticks of sleep remaining" << std::endl;
        setSleep(sleepCounter() - 1);
        return false;
    }
    
    getUnstunned();
    return true;
}

bool Insect::bite()
{
    StudentWorld* world = getWorld();
    bool didDamage = getWorld()->damageRand(getX(), getY(), m_damage, this);
    if (didDamage)
        return true;
    return false;
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
    if (!attemptAct() || mature())
        return;
 
    int rest = 0;
    if (eat())
        rest = randInt(0, 1);
        
    if (!rest)
        move();
    
    setSleep(2);
}

bool BabyGrasshopper::mature()
{
    if (getHP() >= 1600)
    {
        Actor* adult = new AdultGrasshopper(getX(), getY(), getWorld());
        getWorld()->addActor(getX(), getY(), adult);
        loseHP(getHP());
        return true;
    }
    
    return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Adult grasshopper class

void AdultGrasshopper::doSomething()
{
    if (!attemptAct())
        return;
    
    bool skipAct = false;
    
    if (randInt(1, 3) == 3)
    {
        if (bite())
            skipAct = true;
    }
    
    else if (randInt(1, 10) == 10)
    {
        if (jump())
            skipAct = true;
    }
    
    if (!skipAct)
    {
        int rest = 0;
        if (eat())
            rest = randInt(0, 1);
    
        if (!rest)
            move();
    }
    
    setSleep(2);
    return;
    
}

bool AdultGrasshopper::jump()
{
    StudentWorld* world = getWorld();
    int num = 0;
    
    while (num <= 300)
    {
        num++;
        int distance = randInt(0, 10);
        float angle = static_cast<float>(randInt(0, 360));
        int dX = static_cast<int>(distance * cos(angle));
        int dY = static_cast<int>(distance * sin(angle));
        if (dX == 0 && dY == 0)
            continue;
        if (!world->isBlocked(getX() + dX, getY() + dY))
        {
            world->moveActor(getX(), getY(), getX() + dX, getY() + dY, this);
            moveTo(getX() + dX, getY() + dY);
            return true;
        }
    }
   
    return false;
    
}

