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

// Initializes the map, set ticks to 0
int StudentWorld::init()
{
    parseField();
    m_tks = 0;
    return GWSTATUS_CONTINUE_GAME;
}

// This code is here merely to allow the game to build, run, and terminate after you hit enter.
// Notice that the return value GWSTATUS_NO_WINNER will cause our framework to end the simulation.
// Every actor is deactivated after moving, making it unable to be moved again this tick.
int StudentWorld::move()
{
    m_tks++;
    
    for (int x = 1; x < 63; x++)
    {
        for (int y = 1; y < 63; y++)
        {
            for (int i = 0; i < m_actors[x][y].size(); i++)
            {
                if (m_actors[x][y][i]->isActive())
                {
                    m_actors[x][y][i]->doSomething();
                    m_actors[x][y][i]->deactivate();
                }
            }
        }
    }
    
    resetField();
    setDisplayText();
    
    if (m_tks == 2000) // Game should terminate after 2000 ticks, this is only for testing purposes
        return GWSTATUS_NO_WINNER;
    
    return GWSTATUS_CONTINUE_GAME;
}

// Removes all dynamicly allocated memory after the simulation is over
void StudentWorld::cleanUp()
{
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            vector<Actor*>::iterator it = m_actors[x][y].begin();
            while (it != m_actors[x][y].end())
            {
                delete *it;
                it = m_actors[x][y].erase(it);
            }
        }
    }
}

bool StudentWorld::isBlocked(int x, int y) const
{
    if (x < 0 || x >= VIEW_WIDTH || y < 0 || y >= VIEW_WIDTH)
        return true;
    
    if (!m_actors[x][y].empty())
    {
        Actor* actor = m_actors[x][y][0];
        return actor->isBlockage();
    }
    return false;
}

void StudentWorld::moveActor(int oldX, int oldY, int newX, int newY, Actor *actor)
{
    vector<Actor*>::iterator it = m_actors[oldX][oldY].begin();
    while (it != m_actors[oldX][oldY].end())
    {
        if (*it == actor)
        {
            Actor* newActor = *it;
            m_actors[oldX][oldY].erase(it);
            m_actors[newX][newY].push_back(newActor);
            return;
        }
        it++;
    }
    return;
}

int StudentWorld::consumeFood(int x, int y, int amount)
{
    vector<Actor*>::iterator it = m_actors[x][y].begin();
    while (it != m_actors[x][y].end())
    {
        if ((*it)->getType() == FOOD)
        {
            int units = (*it)->getHP();
            int amountEaten = units > amount ? amount : units;
            (*it)->loseHP(amountEaten);
            return amountEaten;
        }
        it++;
    }
    
    return 0;
}

void StudentWorld::stackFood(int x, int y, int amount)
{
    vector<Actor*>::iterator it = m_actors[x][y].begin();
    while (it != m_actors[x][y].end())
    {
        if ((*it)->getType() == FOOD)
        {
            (*it)->gainHP(amount);
            return;
        }
        it++;
    }
    
    Actor* food = new Food(x, y, amount, this);
    addActor(x, y, food);
}

void StudentWorld::stunAOE(int x, int y, int duration)
{
    vector<Actor*>::iterator it = m_actors[x][y].begin();
    while (it != m_actors[x][y].end())
    {
        if ((*it)->getType() == BABY_GH || (*it)->getType() == ANT)
        {
            if (!(*it)->isStunned() && !(*it)->isDead())
                (*it)->getStunned(duration);
        }
        it++;
    }
}

void StudentWorld::damageAOE(int x, int y, int damage)
{
    for (int i = 0; i < m_actors[x][y].size(); i++)
    {
        if ((m_actors[x][y][i]->getType() == BABY_GH || m_actors[x][y][i]->getType() == ANT) && (!m_actors[x][y][i]->isDead()))
        {
            m_actors[x][y][i]->loseHP(damage);
        }
    }
}

bool StudentWorld::damageRand(int x, int y, int damage, Actor* source)
{
    int max = 0;
    int maxpos = -1;
    int faction = source->getFaction();
    
    for (int i = 0; i < m_actors[x][y].size(); i++)
    {
        if ((m_actors[x][y][i]->getFaction() == NEUTRAL || m_actors[x][y][i]->getFaction() != faction) && !m_actors[x][y][i]->isImmobile() && m_actors[x][y][i] != source)
        {
            if (randInt(0, 9999) > max)
                maxpos = i;
        }
    }
    
    if (maxpos != -1)
    {
        m_actors[x][y][maxpos]->loseHP(damage);
        if (randInt(0, 1) == 1 && m_actors[x][y][maxpos]->getType() == ADULT_GH)
            damageRand(x, y, 50, m_actors[x][y][maxpos]);
        return true;
    }
    
    return false;
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
            bool hasItem = true;
            switch (item)
            {
                case (Field::FieldItem::empty):
                    // cout << "emptyyyy" << endl;
                    hasItem = false;
                    break;
                case (Field::FieldItem::anthill0):
                    hasItem = false;
                    break;
                case (Field::FieldItem::anthill1):
                    hasItem = false;
                    break;
                case (Field::FieldItem::anthill2):
                    hasItem = false;
                    break;
                case (Field::FieldItem::anthill3):
                    hasItem = false;
                    break;
                case (Field::FieldItem::food):
                    actor = new Food(x, y, 6000, this);
                    break;
                case (Field::FieldItem::water):
                    actor = new PoolofWater(x, y, this);
                    break;
                case (Field::FieldItem::poison):
                    actor = new Poison(x, y, this);
                    break;
                case (Field::FieldItem::rock):
                    actor = new Pebble(x, y, this);
                    break;
                case (Field::FieldItem::grasshopper):
                    actor = new BabyGrasshopper(x, y, this);
                    break;
            }
            
            if (hasItem)
                addActor(x, y, actor);
        }
    }
}

void StudentWorld::setDisplayText()
{
    string s = "Ticks elapsed: " + to_string(m_tks);
    setGameStatText(s);
}

// Cleans up dead actors and reactivates all inactive (moved) actors
void StudentWorld::resetField()
{
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            std::vector<Actor*>::iterator it = m_actors[x][y].begin();
            while (it != m_actors[x][y].end())
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
        }
    }
}








