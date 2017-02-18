#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <vector>
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;

class Field;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir), m_tks(2000)
    {
	}

	virtual int init()
	{
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
	{
		  // This code is here merely to allow the game to build, run, and terminate after you hit enter.
		  // Notice that the return value GWSTATUS_NO_WINNER will cause our framework to end the simulation.
		return GWSTATUS_NO_WINNER;
	}

	virtual void cleanUp()
	{
        
	}
    
    // Accessors
    

private:
    int m_tks; // Number of ticks, maximum is 2000
    std::vector<Actor*> m_actors[VIEW_WIDTH][VIEW_HEIGHT];
    
    void parseField(); // Reads the field file and place the actors
    void formatText(); // Arranges the text in given format
    void setDisplayText();
};

#endif // STUDENTWORLD_H_
