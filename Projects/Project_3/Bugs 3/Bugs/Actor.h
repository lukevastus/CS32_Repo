#ifndef ACTOR_H_
#define ACTOR_H_

#include "GameConstants.h"
#include "GraphObject.h"
#include <iostream>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constants

// Immunities;
const int AGE_IMMUNE = 0;
const int BITE_IMMUNE = 1;
const int POISON_IMMUNE = 2;
const int STUN_IMMUNE = 3;

// Status
const int ALIVE = 0;
const int DEAD = 1;
const int SLEEPING = 2;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities

class StudentWorld;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Actor class

class Actor: public GraphObject
{
public:
    Actor(int ImageID, int startX, int startY, Direction startDirection, unsigned int depth, int hp, bool isBlockage, bool isImmobile, StudentWorld* world): GraphObject(ImageID, startX, startY, startDirection, 0.3, depth), m_hp(hp), m_world(world), m_blockage(isBlockage), m_immobile(isImmobile), m_active(true)
    {
      
    }
    
    virtual ~Actor()
    {
    
    }
    
    // Accessors
    int getHP() const
    {
        return m_hp;
    }
    
    bool isBlockage() const
    {
        return m_blockage;
    }
    
    bool isImmobile() const
    {
        return m_immobile;
    }
    
    bool isDead() const
    {
        return (m_hp == 0);
    }
    
    bool isActive() const
    {
        return m_active;
    }
    
    StudentWorld* getWorld() const
    {
        return m_world;
    }
    
    // Mutators
    void loseHP(int num)
    {
        m_hp = m_hp - num;
    }
    
    void activate()
    {
        if (!m_immobile)
            m_active = true;
    }
    
    void deactivate()
    {
        if (!m_immobile)
            m_active = false;
    }
    
    virtual void doSomething() = 0;
    
private:
    int m_hp;
    bool m_blockage;
    bool m_immobile;
    bool m_active;
    StudentWorld* m_world;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Pebble class

class Pebble: public Actor
{
public:
    Pebble(int startX, int startY, StudentWorld* world): Actor(IID_ROCK, startX, startY, right, 1, 1, true, true, world)
    {
        
    }
    
    virtual ~Pebble()
    {
    
    }
    
    virtual void doSomething()
    {
        // std::cout << "DUDE wtf can i do i am a stone you piece of shit" << std::endl;
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Insect class

class Insect: public Actor
{
public:
    Insect(int ImageID, int startX, int startY, int hp, int damage, int hunger, int drop, StudentWorld* world): Actor(ImageID, startX, startY, none, 1, hp, false, false, world), m_sleepCounter(0), m_walkCounter(0), m_damage(damage), m_hunger(hunger), m_drop(drop)
    {
        newDir();
    }
    
    virtual ~Insect()
    {
        
    }
    
    // Accessors
    int sleepCounter() const
    {
        return m_sleepCounter;
    }
    
    int getDamage() const
    {
        return m_damage;
    }
    
    int getHunger() const
    {
        return m_hunger;
    }
    
    int getWalkCounter() const
    {
        return m_walkCounter;
    }
    
    // Mutators
    void setSleep(int count)
    {
        m_sleepCounter = count;
    }
    
    void setWalkCounter(int num)
    {
        m_walkCounter = num;
    }
    
    bool attemptAct();

    void dropFood();
    
    // void bite(Actor &other);
    
    bool eat();
    
    void move();
    
    void newDir();
    
    virtual void doSomething() = 0;
    
private:
    int m_sleepCounter;
    int m_walkCounter;
    int m_damage;
    int m_hunger;
    int m_drop;
    
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Baby grasshopper class

class BabyGrasshopper: public Insect
{
public:
    BabyGrasshopper(int startX, int startY, StudentWorld* world): Insect(IID_BABY_GRASSHOPPER, startX, startY, 500, 0, 200, 100, world)
    {
    
    }
    
    virtual ~BabyGrasshopper()
    {
    
    }
    
    virtual void doSomething();
    
    virtual bool doGrasshopperThings();
    // void mature();
};

#endif // ACTOR_H_
