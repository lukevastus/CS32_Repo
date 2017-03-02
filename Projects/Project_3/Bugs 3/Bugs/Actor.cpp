#include "Actor.h"
#include "StudentWorld.h"
#include "Compiler.h"
#include <iostream>
#include <cmath>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Mortal class

bool Mortal::consumeFood(int amount) // Eat food at current grid and convert to HP
{
    StudentWorld* world = getWorld();
    int amountEaten = world->reduceFood(getX(), getY(), amount);
    if (amountEaten > 0)
    {
        gainHP(amountEaten);
        return true;
    }
    
    return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Pool of Water class

void PoolofWater::doSomething()
{
    getWorld()->stunAOE(getX(), getY(), 2);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Poison class

void Poison::doSomething()
{
    getWorld()->damageAOE(getX(), getY(), 150);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Anthill class

void AntHill::doSomething()
{
    loseHP(1);
    if (isDead())
        return;
    
    if (consumeFood(10000))
        return;
    
    if (getHP() >= 2000)
        spawnAnt();
}

void AntHill::spawnAnt() // Spawn an ant at current grid
{
    getWorld()->addActor(getX(), getY(), new Ant(getX(), getY(), getFaction(), m_compiler, getWorld()));
    loseHP(1500);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Insect class

void Insect::loseHP(int amount) // Lose HP
{
    Mortal::loseHP(amount);
    if (isDead())
        dropFood(m_drop);
}

void Insect::getStunned(int duration)
{
    if (!m_stunned)
    {
        m_sleepCounter += duration;
        m_stunned = true;
    }
}

bool Insect::attemptAct() // Checks if the insect is dead or stunned
{
    loseHP(1);
    
    if (isDead())
    {
        return false;
    }
    
    if (m_sleepCounter > 0)
    {
        m_sleepCounter--;
        return false;
    }
    
    return true;
}

bool Insect::bite() // Bite a random insect at current square
{
    StudentWorld* world = getWorld();
    bool didDamage = world->damageRand(getX(), getY(), m_damage, this);
    if (didDamage)
        return true;
    return false;
}

bool Insect::eat()
{
    return consumeFood(m_hunger);
}

bool Insect::move(bool random) // Moves according to self's inbuilt walk counter (if random)
{
    if (m_walkCounter == 0 && random)
    {
        newDir();
        int distance = randInt(2, 10);
        m_walkCounter = distance;
    }
    
    StudentWorld* world = getWorld();
    int newX = getX();
    int newY = getY();
    
    frontGrid(newX, newY);
    
    if (world->isBlocked(newX, newY))
    {
        m_walkCounter = 0;
        return false;
    }
    
    world->moveActor(getX(), getY(), newX, newY, this);
    moveTo(newX, newY);
    
    if (random)
        m_walkCounter--;
    
    m_stunned = false;
    return true;
}

void Insect::newDir() // Gets a random new direction
{
    int dir = randInt(1, 4);
    switch (dir)
    {
        case 1:
            setDirection(up);
            break;
        case 2:
            setDirection(right);
            break;
        case 3:
            setDirection(down);
            break;
        case 4:
            setDirection(left);
            break;
        default:
            break;
    }
}

void Insect::frontGrid(int &x, int &y) // Find the coordinate of the grid in front of self
{
    switch (getDirection())
    {
        case up:
            y++;
            break;
        case right:
            x++;
            break;
        case down:
            y--;
            break;
        case left:
            x--;
            break;
        default:
            break;
    }
}

void Insect::dropFood(int amount) // Add food to current grid
{
    if (amount > 0)
        getWorld()->stackFood(getX(), getY(), amount);
    // std::cout << amount << " dropped the stick!" << std::endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Baby grasshopper class

void BabyGrasshopper::doSomething()
{
    if (!attemptAct() || mature())
        return;
 
    int rest = 0;
    if (eat())
        rest = randInt(0, 1);
        
    if (!rest)
        move(true);
    
    setSleep(2);
}

bool BabyGrasshopper::mature() // Kills self and place an adultgrasshopper
{
    if (getHP() >= 1600)
    {
        Actor* adult = new AdultGrasshopper(getX(), getY(), getWorld());
        getWorld()->addActor(getX(), getY(), adult);
        loseHP(getHP());
        return true;
    }
    
    return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Adult grasshopper class

void AdultGrasshopper::getBitten(int damage)
{
    Insect::getBitten(damage);
    if (randInt(0, 1) == 1)
    {
        // std::cout << "FITE ME!" << std::endl;
        bite();
    }
}

void AdultGrasshopper::doSomething()
{
    if (!attemptAct())
        return;
    
    bool skipAct = false;
    
    if (randInt(1, 3) == 3)
    {
        if (bite())
            skipAct = true;
    }
    
    else if (randInt(1, 10) == 10)
    {
        if (jump())
            skipAct = true;
    }
    
    if (!skipAct)
    {
        int rest = 0;
        if (eat())
            rest = randInt(0, 1);
    
        if (!rest)
            move(true);
    }
    
    setSleep(2);
}

bool AdultGrasshopper::jump() // Hops ro a random grid within radius 10
{
    StudentWorld* world = getWorld();
    int num = 0;
    
    while (num <= 300)
    {
        num++;
        int distance = randInt(0, 10);
        float angle = static_cast<float>(randInt(0, 360));
        int dX = static_cast<int>(distance * cos(angle));
        int dY = static_cast<int>(distance * sin(angle));
        
        if (dX == 0 && dY == 0)
            continue;
        
        if (!world->isBlocked(getX() + dX, getY() + dY))
        {
            world->moveActor(getX(), getY(), getX() + dX, getY() + dY, this);
            moveTo(getX() + dX, getY() + dY);
            return true;
        }
    }
   
    return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Ant class

void Ant::getBitten(int damage)
{
    Insect::getBitten(damage);
    m_bitten = true;
}

void Ant::doSomething()
{
    if (!attemptAct())
        return;
    
    int cmdCounter = 0;
    Compiler::Command cmd;
    
    while (cmdCounter <= 10)
    {
        if (!m_compiler->getCommand(m_insCounter, cmd))
        {
            loseHP(getHP());
            return;
        }
        
        cmdCounter++;
        m_insCounter++;
        
        switch(cmd.opcode)
        {
            case Compiler::invalid:
            case Compiler::label:
                break;
                
            case Compiler::rotateClockwise:
                switch (getDirection())
                {
                    case up:
                        setDirection(right);
                        break;
                    case right:
                        setDirection(down);
                        break;
                    case down:
                        setDirection(left);
                        break;
                    case left:
                        setDirection(up);
                        break;
                    case none:
                        break;
                }
                return;
                
            case Compiler::rotateCounterClockwise:
                switch (getDirection())
                {
                    case up:
                        setDirection(left);
                        break;
                    case right:
                        setDirection(up);
                        break;
                    case down:
                        setDirection(right);
                        break;
                    case left:
                        setDirection(down);
                        break;
                    case none:
                        break;
                }
                return;
                
            case Compiler::moveForward:
                if (move(false))
                {
                    m_prevBlocked = false;
                    m_bitten = false;
                }
                
                else
                    m_prevBlocked = true;
                return;
                
            case Compiler::eatFood:
            {
                int eaten = m_food >= 100 ? 100 : m_food;
                gainHP(eaten);
                m_food -= eaten;
                break;
            }
            
            case Compiler::dropFood:
                dropFood(m_food);
                m_food = 0;
                return;
            
            case Compiler::bite:
                bite();
                return;
            
            case Compiler::pickupFood:
            {
                int attempt = (m_food + 400) > 1800 ? (1800 - m_food) : 400;
                int actual = getWorld()->reduceFood(getX(), getY(), attempt);
                m_food += actual;
                return;
            }
                
            case Compiler::emitPheromone:
                getWorld()->dropPheromone(getX(), getY(), getFaction());
                return;
            
            case Compiler::faceRandomDirection:
                newDir();
                return;
            
            case Compiler::generateRandomNumber:
            {
                int operand = stoi(cmd.operand1);
                m_lastRand = (operand == 0) ? 0 : randInt(0, operand - 1);
                return;
            }
                
            case Compiler::goto_command:
                m_insCounter = stoi(cmd.operand1);
                break;
                
            case Compiler::if_command:
                if (canExecute(cmd.operand1))
                    m_insCounter = stoi(cmd.operand2);
                break;
            
        }
        
    }
    
}

bool Ant::canExecute(std::string op) // Returns true if the if statement evaluates to true
{
    switch(stoi(op))
    {
        case Compiler::last_random_number_was_zero:
            return (m_lastRand == 0);
            
        case Compiler::i_am_carrying_food:
            return (m_food > 0);
            
        case Compiler::i_am_hungry:
            return (getHP() <= 25);
            
        case Compiler::i_am_standing_with_an_enemy:
        {
            int enemyTypes[3] = {ANT, BABY_GH, ADULT_GH};
            for (int i = 0; i < 3; i++)
            {
                if (getWorld()->hasActorType(getX(), getY(), enemyTypes[i], UNSPECIFIED, getFaction()))
                {
                    return true;
                }
            }
            return false;
        }
            
        case Compiler::i_am_standing_on_food:
            return (getWorld()->reduceFood(getX(), getY(), 0) != -1);
            
        case Compiler::i_am_standing_on_my_anthill:
            return (getWorld()->hasActorType(getX(), getY(), ANT_HILL, getFaction()));
            
        case Compiler::i_smell_pheromone_in_front_of_me:
        {
            int newX = getX();
            int newY = getY();
            frontGrid(newX, newY);
            return (getWorld()->hasActorType(newX, newY, PHEROMONE, getFaction()));
        }
            
        case Compiler::i_smell_danger_in_front_of_me:
        {
            int newX = getX();
            int newY = getY();
            frontGrid(newX, newY);
            
            int dangerTypes[4] = {ANT, BABY_GH, ADULT_GH, POISON};
            for (int i = 0; i < 4; i++)
            {
                if (getWorld()->hasActorType(newX, newY, dangerTypes[i], UNSPECIFIED, getFaction()))
                {
                    return true;
                }
            }
            return false;
        }
            
        case Compiler::i_was_bit:
            return m_bitten;
        
        case Compiler::i_was_blocked_from_moving:
            return m_prevBlocked;
    }
    
    return false;
}
























