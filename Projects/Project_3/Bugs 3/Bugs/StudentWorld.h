#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <vector>
#include <string>
#include <iostream>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The StudentWorld class

class Actor;

class Compiler;

class Field;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);

    virtual int init();

    virtual int move();
    
    virtual void cleanUp();
    
    virtual ~StudentWorld();
    
    // Accessors
    bool isBlocked(int x, int y) const;
    
    bool hasActorType(int x, int y, int type, int isFaction, int notFaction = 6) const;
        
    // Mutators
    void addActor(int x, int y, Actor* actor)
    {
        m_actors[x][y].push_back(actor);
    }
    
    void addAntCount(int faction)
    {
        m_antCount[faction]++;
    }
    
    void moveActor(int oldX, int oldY, int newX, int newY, Actor* actor);
    
    int reduceFood(int x, int y, int amount);
    
    void stackFood(int x, int y, int amount);
    
    void stunAOE(int x, int y, int duration);
    
    void damageAOE(int x, int y, int damage);
    
    bool damageRand(int x, int y, int damage, Actor* source);
    
    void dropPheromone(int x, int y, int faction);
    
private:
    bool m_clean;
    int m_tks; // Number of ticks, maximum is 2000
    int m_playerNum; // Number of players
    int m_antCount[4]; // Number of ants produced for each colony
    Compiler* m_compilers[4]; // The compilers for each colony
    std::vector<Actor*> m_actors[VIEW_WIDTH][VIEW_HEIGHT];
    
    void parseField();
    void formatText(); 
    void setDisplayText();
    void resetField();
    void setCompilers();
    int winningColony() const;
};

#endif // STUDENTWORLD_H_
