#include "StudentWorld.h"
#include "Actor.h"
#include "Field.h"
#include <string>
#include <iostream>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The StudentWorld class

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    parseField();
    m_tks = 0;
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_NO_WINNER will cause our framework to end the simulation.
    m_tks++;
    
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            std::vector<Actor*>::iterator it = m_actors[x][y].begin();
            while (it != m_actors[x][y].end())
            {
                if (*it != nullptr)
                {
                    if ((*it)->isActive())
                    {
                        Actor* actor = *it;
                        actor->doSomething();
                        actor->deactivate();
                    }
                }
                it++;
            }
            
        }
    }
    
    resetField();
    setDisplayText();
    
    return 0;
    //return GWSTATUS_NO_WINNER;
}

void StudentWorld::cleanUp()
{
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            std::vector<Actor*>::iterator it = m_actors[x][y].begin();
            while (it != m_actors[x][y].end())
            {
                if (*it != nullptr)
                    delete *it;
                it = m_actors[x][y].erase(it);
            }
        }
    }
}

void StudentWorld::parseField()
{
    Field f;
    string filename = getFieldFilename();
    // cout << filename << endl;
    Field::LoadResult loaded = f.loadField(filename);
    if (loaded == Field::load_fail_bad_format || loaded == Field::load_fail_file_not_found)
        return;
    
    // cout << "LOADED FIELD" << endl;
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            Field::FieldItem item = f.getContentsOf(x, y);
            Actor* actor = nullptr;
            
            switch (item)
            {
                case (Field::FieldItem::empty):
                    // cout << "emptyyyy" << endl;
                    break;
                case (Field::FieldItem::anthill0):
                    break;
                case (Field::FieldItem::anthill1):
                    break;
                case (Field::FieldItem::anthill2):
                    break;
                case (Field::FieldItem::anthill3):
                    break;
                case (Field::FieldItem::food):
                    break;
                case (Field::FieldItem::water):
                    break;
                case (Field::FieldItem::poison):
                    break;
                    
                case (Field::FieldItem::rock):
                    actor = new Pebble(x, y, this);
                    break;
                case (Field::FieldItem::grasshopper):
                    actor = new BabyGrasshopper(x, y, this);
                    break;
            }
            
            addActor(x, y, actor);
        }
    }
}

bool StudentWorld::isBlocked(int x, int y) const
{
    if (!m_actors[x][y].empty())
    {
        Actor* actor = m_actors[x][y][0];
        if (actor != nullptr)
            return actor->isBlockage();
    }
    return false;
}

void StudentWorld::setDisplayText()
{
    string s = "Ticks elapsed: " + to_string(m_tks);
    setGameStatText(s);
}

void StudentWorld::moveActor(int oldX, int oldY, int newX, int newY, Actor *actor)
{
    vector<Actor*>::iterator it = m_actors[oldX][oldY].begin();
    while (it != m_actors[oldX][oldY].end())
    {
        if (*it == actor)
            break;
        it++;
    }
    
    Actor* newActor = *it;
    *it = nullptr;
    m_actors[newX][newY].push_back(newActor);
}

void StudentWorld::resetField()
{
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            std::vector<Actor*>::iterator it = m_actors[x][y].begin();
            while (it != m_actors[x][y].end())
            {
                if (*it != nullptr)
                {
                    if ((*it)->isDead())
                    {
                        delete *it;
                        it = m_actors[x][y].erase(it);
                    }
                    
                    else
                    {
                        (*it)->activate();
                        it++;
                    }
                }
                else
                    it++;
            }
        }
    }
}








