#ifndef ACTOR_H_
#define ACTOR_H_

#include "GameConstants.h"
#include "GraphObject.h"
#include <iostream>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constants

// TYPES OF ACTORS
const int NOT_SPECIFIED = 0;
const int ANT_HILL = 1;
const int POISON = 2;
const int FOOD = 3;
const int WATER_POOL = 4;
const int ROCK = 5;
const int BABY_GH = 6;
const int ADULT_GH = 7;
const int PHEROMONE = 8;
const int ANT = 9;

// Factions
const int NEUTRAL = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities

class StudentWorld;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Actor class

class Actor: public GraphObject
{
public:
    Actor(int ImageID, int startX, int startY, Direction startDirection, unsigned int depth, int type, int hp, int drop, bool isBlockage, bool isImmobile, int faction, StudentWorld* world): GraphObject(ImageID, startX, startY, startDirection, depth), m_type(type), m_hp(hp), m_drop(drop), m_world(world), m_blockage(isBlockage), m_immobile(isImmobile), m_active(true), m_stunned(false), m_sleepCounter(0), m_faction(faction)
    {
      
    }
    
    virtual ~Actor()
    {
    
    }
    
    // Accessors
    int getType() const
    {
        return m_type;
    }
    
    int getFaction() const
    {
        return m_faction;
    }
    
    int getHP() const
    {
        return m_hp;
    }
    
    int sleepCounter() const
    {
        return m_sleepCounter;
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
        return (m_hp <= 0);
    }
    
    bool isActive() const
    {
        return m_active;
    }
    
    bool isStunned() const
    {
        return m_stunned;
    }
    
    StudentWorld* getWorld() const
    {
        return m_world;
    }
    
    // Mutators
    void gainHP(int num)
    {
        m_hp = m_hp + num;
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
    
    void getStunned(int duration)
    {
        m_stunned = true;
        setSleep(m_sleepCounter + duration);
    }
    
    void getUnstunned()
    {
        m_stunned = false;
    }
    
    void setSleep(int count)
    {
        m_sleepCounter = count;
    }
    
    void loseHP(int num);

    void dropFood(int amount);

    virtual void doSomething() = 0;
    
private:
    int m_type;
    int m_hp;
    int m_sleepCounter;
    int m_drop;
    int m_faction;
    bool m_blockage;
    bool m_immobile;
    bool m_active;
    bool m_stunned;
    StudentWorld* m_world;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Pebble class

class Pebble: public Actor
{
public:
    Pebble(int startX, int startY, StudentWorld* world): Actor(IID_ROCK, startX, startY, right, 1, ROCK, 100, 0, true, true, NEUTRAL, world)
    {
        
    }
    
    virtual ~Pebble()
    {
    
    }
    
    virtual void doSomething()
    {

    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Food class

class Food: public Actor
{
public:
    Food(int startX, int startY, int units, StudentWorld* world): Actor(IID_FOOD, startX, startY, right, 2, FOOD, units, 0, false, true, NEUTRAL, world)
    {
        
    }
    
    virtual ~Food()
    {
    
    }
    
    virtual void doSomething()
    {
    
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Pool of Water class

class PoolofWater: public Actor
{
public:
    PoolofWater(int startX, int startY, StudentWorld* world): Actor(IID_WATER_POOL, startX, startY, right, 2, WATER_POOL, 100, 0, false, true, NEUTRAL, world)
    {
        
    }
    
    virtual ~PoolofWater()
    {
        
    }
    
    virtual void doSomething();
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Poison class

class Poison: public Actor
{
public:
    Poison(int startX, int startY, StudentWorld* world): Actor(IID_POISON, startX, startY, right, 2, POISON, 100, 0, false, true, NEUTRAL, world)
    {
        
    }
    
    virtual ~Poison()
    {
        
    }
    
    virtual void doSomething();
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Insect class

class Insect: public Actor
{
public:
    Insect(int ImageID, int startX, int startY, int type, int hp, int damage, int hunger, int drop, int faction, StudentWorld* world): Actor(ImageID, startX, startY, none, 1, type, hp, drop, false, false, faction, world), m_walkCounter(0), m_damage(damage), m_hunger(hunger)
    {
        newDir();
    }
    
    virtual ~Insect()
    {
        
    }
    
    // Accessors
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
    
    void setWalkCounter(int num)
    {
        m_walkCounter = num;
    }
    
    bool attemptAct();
    
    bool bite();
    
    bool eat();
    
    void move();
    
    void newDir();
    
    virtual void doSomething() = 0;
    
private:
    int m_walkCounter;
    int m_damage;
    int m_hunger;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Baby grasshopper class

class BabyGrasshopper: public Insect
{
public:
    BabyGrasshopper(int startX, int startY, StudentWorld* world): Insect(IID_BABY_GRASSHOPPER, startX, startY, BABY_GH, 500, 0, 200, 100, NEUTRAL, world)
    {
    
    }
    
    virtual ~BabyGrasshopper()
    {
    
    }
    
    virtual void doSomething();
    
    bool mature();
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Adult grasshopper class

class AdultGrasshopper: public Insect
{
public:
    AdultGrasshopper(int startX, int startY, StudentWorld* world): Insect(IID_ADULT_GRASSHOPPER, startX, startY, ADULT_GH, 1600, 50, 200, 100, NEUTRAL, world)
    {
    
    }
    
    virtual ~AdultGrasshopper()
    {
    
    }
    
    virtual void doSomething();
    
    bool jump();
};

#endif // ACTOR_H_
