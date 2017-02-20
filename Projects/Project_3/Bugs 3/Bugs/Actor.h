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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities

class StudentWorld;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Actor class

class Actor: public GraphObject
{
public:
    Actor(int ImageID, int startX, int startY, Direction startDirection, unsigned int depth, int type, int hp, bool isBlockage, bool isImmobile, StudentWorld* world): GraphObject(ImageID, startX, startY, startDirection, depth), m_type(type), m_hp(hp), m_world(world), m_blockage(isBlockage), m_immobile(isImmobile), m_active(true)
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
        return (m_hp <= 0);
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
    void gainHP(int num)
    {
        m_hp = m_hp + num;
    }
    
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
    int m_type;
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
    Pebble(int startX, int startY, StudentWorld* world): Actor(IID_ROCK, startX, startY, right, 1, ROCK, 100, true, true, world)
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
// The Food class

class Food: public Actor
{
public:
    Food(int startX, int startY, int units, StudentWorld* world): Actor(IID_FOOD, startX, startY, right, 2, FOOD, units, false, true, world)
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
// The Insect class

class Insect: public Actor
{
public:
    Insect(int ImageID, int startX, int startY, int type, int hp, int damage, int hunger, int drop, StudentWorld* world): Actor(ImageID, startX, startY, none, 1, type, hp, false, false, world), m_sleepCounter(0), m_walkCounter(0), m_damage(damage), m_hunger(hunger), m_drop(drop)
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
    BabyGrasshopper(int startX, int startY, StudentWorld* world): Insect(IID_BABY_GRASSHOPPER, startX, startY, BABY_GH, 500, 0, 200, 100, world)
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
