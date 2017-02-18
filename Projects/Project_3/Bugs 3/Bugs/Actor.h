#ifndef ACTOR_H_
#define ACTOR_H_

#include "GameConstants.h"
#include "GraphObject.h"

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

GraphObject::Direction randDir()
{
    int dir = randInt(1, 4);
    switch (dir)
    {
        case 1:
            return GraphObject::up;
        case 2:
            return GraphObject::right;
        case 3:
            return GraphObject::down;
        case 4:
            return GraphObject::left;
    }
    return GraphObject::none;
}

class StudentWorld;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Actor class
class Actor: public GraphObject
{
public:
    Actor(int ImageID, int startX, int startY, Direction startDirection, unsigned int depth, int hp, bool ageI, bool biteI, bool poiI, bool stunI, StudentWorld* world): GraphObject(ImageID, startX, startY, startDirection, 1.0, depth), m_hp(hp), m_world(world)
    {
        m_Immunities[0] = ageI;
        m_Immunities[1] = biteI;
        m_Immunities[2] = poiI;
        m_Immunities[3] = stunI;
    }
    
    virtual ~Actor()
    {
    
    }
    
    // Accessors
    int getHP() const
    {
        return m_hp;
    }
    
    bool hasImmunity(int immuneType) const
    {
        return m_Immunities[immuneType];
    }
    
    bool isDead() const
    {
        return (m_hp == 0);
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
    
    virtual void doSomething() = 0;
    
private:
    int m_hp;
    bool m_Immunities[4];
    StudentWorld* m_world;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Pebble class
class Pebble: public Actor
{
public:
    Pebble(int startX, int startY, StudentWorld* world): Actor(IID_ROCK, startX, startY, right, 1, 1, true, true, true, true, world)
    {
        
    }
    
    virtual ~Pebble()
    {
    
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Insect class
class Insect: public Actor
{
public:
    Insect(int ImageID, int startX, int startY, Direction startDirection, int hp, int damage, int hunger, int drop, bool poiI, bool stunI, StudentWorld* world): Actor(ImageID, startX, startY, startDirection, 1, hp, false, false, poiI, stunI, world), m_sleepCounter(0), m_damage(damage), m_hunger(hunger), m_drop(drop)
    {
        
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
    
    // Mutators
    
    bool attemptAct();
    
    void age()
    {
        Actor::loseHP(1);
    }
    
    void dropFood();
    
    // void bite(Actor &other);
    
    // void eat();
    
    void move();
    
    void setSleep(int count)
    {
        m_sleepCounter = count;
    }
    
private:
    int m_sleepCounter;
    int m_damage;
    int m_hunger;
    int m_drop;
    
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Baby grasshopper class
class BabyGrasshopper: public Insect
{
public:
    BabyGrasshopper(int startX, int startY, Direction startDirection, StudentWorld* world): Insect(IID_BABY_GRASSHOPPER, startX, startY, randDir(), 500, 0, 200, 100, false, false, world)
    {
        
    }
    
    virtual ~BabyGrasshopper()
    {
    
    }
    
    virtual void doSomething();

    // void mature();
};
#endif // ACTOR_H_
