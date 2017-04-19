#include "StudentWorld.h"
#include "Actor.h"
#include "Compiler.h"
#include "Field.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The StudentWorld class

StudentWorld::StudentWorld(string assetDir): GameWorld(assetDir), m_clean(true), m_tks(0), m_playerNum(0), m_winningNum(5), m_winningColony(-1)
{
    for (int i = 0; i < 4; i++)
    {
        m_antCount[i] = 0;
        m_compilers[i] = nullptr;
    }
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init() // Initializes the map
{
    std::vector<string> files = getFilenamesOfAntPrograms();
    for (int i = 0; i < files.size(); i++)
    {
        std::string error;
        m_compilers[i] = new Compiler;
        if (!m_compilers[i]->compile(files[i], error))
        {
            setError(files[i] + " " + error);
            return GWSTATUS_LEVEL_ERROR;
        }
        m_playerNum++;
    }
    
    parseField();
    m_clean = false;
    return GWSTATUS_CONTINUE_GAME;
}

// This code is here merely to allow the game to build, run, and terminate after you hit enter.
// Notice that the return value GWSTATUS_NO_WINNER will cause our framework to end the simulation.
// Every actor is deactivated after moving, making it unable to be moved again this tick.
int StudentWorld::move()
{
    m_tks++;
    
    for (int x = 1; x < VIEW_WIDTH - 1; x++)
    {
        for (int y = 1; y < VIEW_HEIGHT - 1; y++)
        {
            for (int i = 0; i < m_actors[x][y].size(); i++)
            {
                if (m_actors[x][y][i]->isActive() && !m_actors[x][y][i]->isDead())
                {
                    m_actors[x][y][i]->doSomething();
                    m_actors[x][y][i]->deactivate();
                }
            }
        }
    }
    
    resetField();
    setDisplayText();
    
    if (m_tks == GAME_LENGTH) // Game should terminate after 2000 ticks, this is only for testing purposes
    {
        if (m_winningColony != -1)
        {
            setWinner(m_compilers[m_winningColony]->getColonyName());
            return GWSTATUS_PLAYER_WON;
        }
        return GWSTATUS_NO_WINNER;
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() // Removes all dynamicly allocated memory after the simulation is over
{
    if (m_clean)
        return;
    
    for (int x = 0; x < VIEW_WIDTH; x++)
    {
        for (int y = 0; y < VIEW_HEIGHT; y++)
        {
            vector<Actor*>::iterator it = m_actors[x][y].begin();
            while (it != m_actors[x][y].end())
            {
                delete *it;
                it = m_actors[x][y].erase(it);
            }
        }
    }
    
    for (int i = 0; i < m_playerNum; i++)
    {
        if (m_compilers[i] != nullptr)
            delete m_compilers[i];
    }
    
    m_clean = true;
}

bool StudentWorld::isBlocked(int x, int y) const // Check if grid is blocked by a pebble
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

bool StudentWorld::hasActorType(int x, int y, int type, int isFaction, int notFaction) const // Check if an alive actor with faction isFaction OR with faction not notFaction is on grid
{
    for (int i = 0; i < m_actors[x][y].size(); i++)
    {
        if (m_actors[x][y][i]->getType() == type && !m_actors[x][y][i]->isDead())
        {
            if (isFaction != UNSPECIFIED && m_actors[x][y][i]->getFaction() == isFaction)
                return true;
            
            if (notFaction != UNSPECIFIED && m_actors[x][y][i]->getFaction() != notFaction)
                return true;
        }
    }
    return false;
}

void StudentWorld::addActor(int x, int y, Actor *actor)
{
    m_actors[x][y].push_back(actor);
    if (actor->getType() == ANT)
        addAntCount(actor->getFaction());
}

void StudentWorld::moveActor(int oldX, int oldY, int newX, int newY, Actor *actor) // Move the actor to a new grid position
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

int StudentWorld::reduceFood(int x, int y, int amount) // Reduce the amount of food present on grid (x, y)
{
    vector<Actor*>::iterator it = m_actors[x][y].begin();
    while (it != m_actors[x][y].end())
    {
        if ((*it)->getType() == FOOD && !(*it)->isDead())
        {
            int units = (*it)->getHP();
            int amountEaten = units > amount ? amount : units;
            (*it)->loseHP(amountEaten);
            return amountEaten;
        }
        it++;
    }
    
    return -1; // Food not found
}

void StudentWorld::stackFood(int x, int y, int amount) // Puts a Food object on grid (x, y). If there's already a Food then increase its strength
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

void StudentWorld::stunAOE(int x, int y, int duration) // Stuns all vulnerable insects on grid (x, y)
{
    vector<Actor*>::iterator it = m_actors[x][y].begin();
    while (it != m_actors[x][y].end())
    {
        if (!(*it)->isDead())
            (*it)->getStunned(duration);
        it++;
    }
}

void StudentWorld::damageAOE(int x, int y, int damage) // Damages all vulnerable insects on grid (x, y)
{
    for (int i = 0; i < m_actors[x][y].size(); i++)
    {
        if ((m_actors[x][y][i]->getType() == BABY_GH || m_actors[x][y][i]->getType() == ANT) && !m_actors[x][y][i]->isDead())
            m_actors[x][y][i]->loseHP(damage);
    }
}

bool StudentWorld::damageRand(int x, int y, int damage, Actor* source) // Randomly deals damage to one of the insects (which is not the source of damage) on grid (x, y)
{
    int max = 0;
    int maxpos = -1;
    int faction = source->getFaction();
    
    for (int i = 0; i < m_actors[x][y].size(); i++)
    {
        if ((m_actors[x][y][i]->getFaction() == NEUTRAL || m_actors[x][y][i]->getFaction() != faction) && !m_actors[x][y][i]->isImmobile() && m_actors[x][y][i] != source && !m_actors[x][y][i]->isDead())
        {
            if (randInt(0, 9999) > max)
                maxpos = i;
        }
    }
    
    if (maxpos != -1)
    {
        m_actors[x][y][maxpos]->getBitten(damage);
        return true;
    }
    
    return false;
}

void StudentWorld::dropPheromone(int x, int y, int faction) // Puts a Pheromone object on grid (x, y). If there's already a Pheromone then increase its strength
{
    vector<Actor*>::iterator it = m_actors[x][y].begin();
    while (it != m_actors[x][y].end())
    {
        if ((*it)->getType() == PHEROMONE && (*it)->getFaction() == faction)
        {
            int added = ((*it)->getHP() + 256) > 768 ? (768 - (*it)->getHP()) : 256;
            (*it)->gainHP(added);
            return;
        }
        it++;
    }
    
    Actor* pheromone = new Pheromone(x, y, faction, this);
    addActor(x, y, pheromone);
}

void StudentWorld::parseField() // Reads the field.txt file and put the actors in their initial positions
{
    Field f;
    string filename = getFieldFilename();
    Field::LoadResult loaded = f.loadField(filename);
    if (loaded == Field::load_fail_bad_format || loaded == Field::load_fail_file_not_found)
        return;
    
    for (int x = 0; x < VIEW_WIDTH; x++)
    {
        for (int y = 0; y < VIEW_HEIGHT; y++)
        {
            Field::FieldItem item = f.getContentsOf(x, y);
            Actor* actor = nullptr;
            bool hasItem = true;
            switch (item)
            {
                case (Field::FieldItem::empty):
                    hasItem = false;
                    break;
                case (Field::FieldItem::anthill0):
                    if (m_playerNum > 0)
                        actor = new AntHill(x, y, 0, m_compilers[0], this);
                    else hasItem = false;
                    break;
                case (Field::FieldItem::anthill1):
                    if (m_playerNum > 1)
                        actor = new AntHill(x, y, 1, m_compilers[1], this);
                    else hasItem = false;
                    break;
                case (Field::FieldItem::anthill2):
                    if (m_playerNum > 2)
                        actor = new AntHill(x, y, 2, m_compilers[2], this);
                    else hasItem = false;
                    break;
                case (Field::FieldItem::anthill3):
                    if (m_playerNum > 3)
                        actor = new AntHill(x, y, 3, m_compilers[3], this);
                    else hasItem = false;
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

void StudentWorld::setDisplayText() // Configures the displayed player information
{
    countAnts();
    ostringstream text;
    text << setw(5) << GAME_LENGTH - m_tks;
    string display = "Ticks:" + text.str() + " - ";
    int winner = m_winningColony;
    for (int i = 0; i < m_playerNum; i++)
    {
        display += (m_compilers[i]->getColonyName());
        if (i == winner)
            display += '*';
        
        display += ": ";
        ostringstream num;
        num.fill('0');
        num << setw(2) << m_antCount[i];
        display += (num.str() + "  ");
    }
    
    setGameStatText(display);
}

void StudentWorld::resetField() // Cleans up dead actors and reactivates all inactive (moved) actors
{
    for (int x = 0; x < VIEW_WIDTH; x++)
    {
        for (int y = 0; y < VIEW_HEIGHT; y++)
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

void StudentWorld::countAnts() // Counts the number of ants and find the colony that is winning
{
    int winner = -1;
    int maxAnt = 0;
    for (int i = 0; i < m_playerNum; i++)
    {
        if (m_antCount[i] > maxAnt && m_antCount[i] > m_winningNum)
        {
            winner = i;
            maxAnt = m_antCount[i];
        }
    }
    
    if (winner != -1)
    {
        m_winningNum = m_antCount[winner];
        m_winningColony = winner;
    }
}





