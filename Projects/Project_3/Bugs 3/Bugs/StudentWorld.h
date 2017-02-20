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

class Field;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
    {
	}

    virtual int init();

    virtual int move();
    
    virtual void cleanUp();
    
    virtual ~StudentWorld();
    
    // Accessors
    bool isBlocked(int x, int y) const;
        
    // Mutators
    void addActor(int x, int y, Actor* actor)
    {
        m_actors[x][y].push_back(actor);
    }
    
    void moveActor(int oldX, int oldY, int newX, int newY, Actor* actor);
    
    int consumeFood(int x, int y, int amount);
    
private:
    int m_tks; // Number of ticks, maximum is 2000
    std::vector<Actor*> m_actors[VIEW_WIDTH][VIEW_HEIGHT];
    
    void parseField();
    void formatText(); 
    void setDisplayText();
    void resetField();
};

#endif // STUDENTWORLD_H_
