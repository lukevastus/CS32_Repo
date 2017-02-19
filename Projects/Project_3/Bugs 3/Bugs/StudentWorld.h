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
	 : GameWorld(assetDir), m_tks(2000)
    {
	}

    virtual int init();

    virtual int move();
    
    virtual void cleanUp();
    
    virtual ~StudentWorld();
    
    // Accessors
    
    
    // Mutators
    void addActor(int x, int y, Actor* actor)
    {
        m_actors[x][y].push_back(actor);
    }
    
    

    
private:
    int m_tks; // Number of ticks, maximum is 2000
    std::vector<Actor*> m_actors[VIEW_WIDTH][VIEW_HEIGHT];
    
    void parseField(); // Reads the field file and place the actors
    void formatText(); // Arranges the text in given format
    void setDisplayText();
};

#endif // STUDENTWORLD_H_
