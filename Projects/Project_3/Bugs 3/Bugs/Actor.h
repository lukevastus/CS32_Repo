#ifndef ACTOR_H_
#define ACTOR_H_

#include "GameConstants.h"
#include "GraphObject.h"
#include <iostream>
#include <string>

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
const int NEUTRAL = 5;
const int UNSPECIFIED = 6;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities

class StudentWorld;
class Compiler;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Actor class

class Actor: public GraphObject
{
public:
    Actor(int ImageID, int startX, int startY, Direction startDirection, unsigned int depth, int type, bool isBlockage, bool isImmobile, int faction, StudentWorld* world): GraphObject(ImageID, startX, startY, startDirection, depth), m_type(type), m_world(world), m_blockage(isBlockage), m_immobile(isImmobile), m_active(true), m_faction(faction)
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
    
    bool isBlockage() const
    {
        return m_blockage;
    }
    
    bool isImmobile() const
    {
        return m_immobile;
    }
    
    bool isActive() const
    {
        return m_active;
    }
    
    StudentWorld* getWorld() const
    {
        return m_world;
    }
    
    virtual int getHP() const = 0;

    virtual bool isDead() const = 0;

    
    // Mutators
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
    
    virtual void getStunned(int duration)
    {
    
    }
    
    virtual void getBitten(int damage)
    {
    
    }
    
    virtual void gainHP(int amount)
    {
    
    }

    virtual void loseHP(int amount)
    {
    
    }

    virtual void doSomething() = 0;
    
private:
    int m_type;
    int m_drop;
    int m_faction;
    bool m_blockage;
    bool m_immobile;
    bool m_active;
    StudentWorld* m_world;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Terrain class

class Terrain: public Actor
{
public:
    Terrain(int ImageID, int startX, int startY, int depth, int type, bool isBlockage, StudentWorld* world): Actor(ImageID, startX, startY, right, depth, type, isBlockage, true, NEUTRAL, world)
    {
    
    }
    
    virtual ~Terrain()
    {
    
    }
    
    virtual int getHP() const
    {
        return 0;
    }
    
    virtual bool isDead() const
    {
        return false;
    }
    
    virtual void doSomething() = 0;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Pebble class

class Pebble: public Terrain
{
public:
    Pebble(int startX, int startY, StudentWorld* world): Terrain(IID_ROCK, startX, startY, 1, ROCK, true, world)
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
// The Poison class

class Poison: public Terrain
{
public:
    Poison(int startX, int startY, StudentWorld* world): Terrain(IID_POISON, startX, startY, 2, POISON, false, world)
    {
        
    }
    
    virtual ~Poison()
    {
        
    }
    
    virtual void doSomething();
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Pool of Water class

class PoolofWater: public Terrain
{
public:
    PoolofWater(int startX, int startY, StudentWorld* world): Terrain(IID_WATER_POOL, startX, startY, 2, WATER_POOL, false, world)
    {
        
    }
    
    virtual ~PoolofWater()
    {
        
    }
    
    virtual void doSomething();
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Mortal class

class Mortal: public Actor
{
public:
    Mortal(int ImageID, int startX, int startY, Direction startDirection, int depth, int type, int HP, bool isImmobile, int faction, StudentWorld* world):Actor(ImageID, startX, startY, startDirection, depth, type, false, isImmobile, faction, world), m_HP(HP)
    {
    
    }
    
    virtual ~Mortal()
    {
    
    }
    
    // Accessors
    virtual int getHP() const
    {
        return m_HP;
    }
    
    virtual bool isDead() const
    {
        return (m_HP <= 0);
    }
    
    //Mutators
    virtual void gainHP(int amount)
    {
        m_HP += amount;
    }
    
    virtual void loseHP(int amount)
    {
        m_HP -= amount;
    }
    
    bool consumeFood(int amount);

    virtual void doSomething() = 0;
    
private:
    int m_HP;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Food class

class Food: public Mortal
{
public:
    Food(int startX, int startY, int units, StudentWorld* world): Mortal(IID_FOOD, startX, startY, right, 2, FOOD, units, true, NEUTRAL, world)
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
// The Pheromone class

class Pheromone: public Mortal
{
public:
    Pheromone(int startX, int startY, int faction, StudentWorld* world): Mortal(faction + 11, startX, startY, right, 2, PHEROMONE, 256, true, faction, world)
    {
    
    }
    
    virtual ~Pheromone()
    {
    
    }
    
    virtual void doSomething()
    {
        loseHP(1);
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Anthill class

class AntHill: public Mortal
{
public:
    AntHill(int startX, int startY, int faction, Compiler* compiler, StudentWorld* world): Mortal(IID_ANT_HILL, startX, startY, right, 2, ANT_HILL, 8999, true, faction, world), m_compiler(compiler)
    {
    
    }
    
    virtual ~AntHill()
    {
    
    }
    
    virtual void doSomething();
    
private:
    Compiler* m_compiler;
    void spawnAnt();
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Insect class

class Insect: public Mortal
{
public:
    Insect(int ImageID, int startX, int startY, int type, int hp, int damage, int hunger, int drop, int faction, StudentWorld* world): Mortal(ImageID, startX, startY, none, 1, type, hp, false, faction, world), m_walkCounter(0), m_sleepCounter(0), m_damage(damage), m_hunger(hunger), m_drop(drop), m_stunned(false)
    {
        newDir();
    }
    
    virtual ~Insect()
    {
        
    }
    
    // Mutators    
    void setSleep(int num)
    {
        m_sleepCounter = num;
    }
    
    bool attemptAct();
    
    bool bite();
    
    bool eat();
    
    bool move(bool random);
    
    void newDir();
    
    void frontGrid(int &x, int &y);
    
    void dropFood(int amount);
    
    virtual void loseHP(int amount);
    
    virtual void getStunned(int duration);
    
    void getUnstunned()
    {
        m_stunned = false;
    }
    
    virtual void getBitten(int damage)
    {
        // std::cout << "ArgGGghhh!" << std::endl;
        loseHP(damage);
    }
    
    virtual void doSomething() = 0;
    
private:
    int m_walkCounter;
    int m_sleepCounter;
    int m_damage;
    int m_hunger;
    int m_drop;
    bool m_stunned;
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

private:
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
    
    virtual void getBitten(int damage);
    
    virtual void getStunned(int duration)
    {
    
    }
    
    virtual void doSomething();
    
private:
    bool jump();
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Ant class

class Ant: public Insect
{
public:
    Ant(int startX, int startY, int faction, Compiler* compiler, StudentWorld* world): Insect(faction, startX, startY, ANT, 1500, 15, 0, 100, faction, world), m_food(0), m_lastRand(0), m_insCounter(0), m_prevBlocked(false), m_bitten(false), m_compiler(compiler)
    {
        
    }

    virtual ~Ant()
    {
    
    }
    
    virtual void getBitten(int damage);
    
    virtual void doSomething();

private:
    int m_food;
    int m_lastRand;
    int m_insCounter;
    bool m_prevBlocked;
    bool m_bitten;
    Compiler* m_compiler;
    
    bool canExecute(std::string op);
};

#endif // ACTOR_H_
