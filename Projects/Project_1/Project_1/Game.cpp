//
//  Game.cpp
//  Project_1
//
//  Created by Runjia Li on 1/9/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "Game.h"
#include "globals.h"
#include "Arena.h"
#include "Player.h"
#include "History.h"
using namespace std;

Game::Game(int rows, int cols, int nRats)
{
    if (nRats < 0)
    {
        cout << "***** Cannot create Game with negative number of rats!" << endl;
        exit(1);
    }
    if (nRats > MAXRATS)
    {
        cout << "***** Trying to create Game with " << nRats
        << " rats; only " << MAXRATS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nRats > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the rats!" << endl;
        exit(1);
    }
    
    // Create arena
    m_arena = new Arena(rows, cols);
    
    // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);
    
    // Populate with rats
    while (nRats > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addRat(r, c);
        nRats--;
    }
}

Game::~Game()
{
    delete m_arena;
}

// Jerome Luo's AI implementation:
bool existance(int secondary, int priority[], int num_1)
{
    for (int pos_1 = 0; pos_1 < num_1; pos_1++)
    {
        if (secondary == priority[pos_1])
            return true;
    }
    return false;
}

bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    int priority[4];
    int num_1 = 0;
    int num_2 = 0;
    int secondary[4] = { NORTH, EAST, SOUTH, WEST };
    double possibilities[4] = {0, 0, 0, 0};
    
    if (r - 1 >= 1 && a.numberOfRatsAt(r - 1, c) == 0)
    {
        priority[num_1] = NORTH;
        num_1++;
        num_2++;
    }
    else if (r - 1 < 1)
        num_2++;
    
    if (c + 1 <= a.cols() && a.numberOfRatsAt(r, c + 1) == 0)
    {
        priority[num_1] = EAST;
        num_1++;
        num_2++;
    }
    else if (c + 1 > a.cols())
        num_2++;
    
    if (r + 1 <= a.rows() && a.numberOfRatsAt(r + 1, c) == 0)
    {
        priority[num_1] = SOUTH;
        num_1++;
        num_2++;
    }
    else if (r + 1 > a.rows())
        num_2++;
    
    if (c - 1 >= 1 && a.numberOfRatsAt(r, c - 1) == 0)
    {
        priority[num_1] = WEST;
        num_1++;
        num_2++;
    }
    else if (c - 1 < 1)
        num_2++;
    
    if (num_2 == 4 && a.getCellStatus(r, c) == EMPTY)
        return false;
    
    if (c + 1 <= a.cols() && r - 1 >= 1)
    {
        possibilities[NORTH] = possibilities[NORTH] + 0.25 * a.numberOfRatsAt(r - 1, c + 1);
        possibilities[EAST] = possibilities[EAST] + 0.25 * a.numberOfRatsAt(r - 1, c + 1);
    }
    
    if (c + 1 <= a.cols() && r + 1 <= a.rows())
    {
        possibilities[SOUTH] = possibilities[SOUTH] + 0.25 * a.numberOfRatsAt(r + 1, c + 1);
        possibilities[EAST] = possibilities[EAST] + 0.25 * a.numberOfRatsAt(r + 1, c + 1);
    }
    
    if (c - 1 >= 1 && r - 1 >= 1)
    {
        possibilities[NORTH] = possibilities[NORTH] + 0.25 * a.numberOfRatsAt(r - 1, c - 1);
        possibilities[WEST] = possibilities[WEST] + 0.25 * a.numberOfRatsAt(r - 1, c - 1);
    }
    
    if (c - 1 >= 1 && r + 1 <= a.rows())
    {
        possibilities[SOUTH] = possibilities[SOUTH] + 0.25 * a.numberOfRatsAt(r + 1, c - 1);
        possibilities[WEST] = possibilities[WEST] + 0.25 * a.numberOfRatsAt(r + 1, c - 1);
    }
    
    if (c + 2 <= a.cols())
        possibilities[EAST] = possibilities[EAST] + 0.25 * a.numberOfRatsAt(r, c + 2);
    
    if (c - 2 >= 1)
        possibilities[WEST] = possibilities[WEST] + 0.25 * a.numberOfRatsAt(r, c - 2);
    
    if (r + 2 <= a.rows())
        possibilities[SOUTH] = possibilities[SOUTH] + 0.25 * a.numberOfRatsAt(r + 2, c);
    
    if (r - 2 >= 1)
        possibilities[NORTH] = possibilities[NORTH] + 0.25 * a.numberOfRatsAt(r - 2, c);
    
    for (int pos_1 = 0; pos_1 < 4; pos_1++)
        for (int pos_2 = pos_1; pos_2 < 4; pos_2++)
            if (possibilities[pos_1] > possibilities[pos_2])
            {
                swap(possibilities[pos_1], possibilities[pos_2]);
                swap(secondary[pos_1], secondary[pos_2]);
            }
    
    int pos_1;
    int pos_2 = 0;
    for (pos_1 = 0; pos_1 < 3; pos_1++)
    {
        if (existance(secondary[pos_1], priority, num_1))
        {
            if (possibilities[pos_1] == possibilities[pos_1 + 1] &&
                existance(secondary[pos_1 + 1], priority, num_1))
                continue;
            else
            {
                bestDir = secondary[randInt(pos_2, pos_1)];
                return true;
            }
        }
        pos_2++;
    }
    
    if (pos_1 == 3 && existance(secondary[3], priority, num_1))
    {
        bestDir = secondary[randInt(pos_2, 3)];
        return true;
    }
    
    return false;
}

// Mr.Smallberg's AI implementation:
/*
int computeDanger(const Arena& a, int r, int c)
{
    // Our measure of danger will be the number of rats that might move
    // to position r,c.  If a rat is at that position, it is fatal,
    // so a large value is returned.
    
    if (a.numberOfRatsAt(r,c) > 0)
        return MAXRATS+1;
    
    int danger = 0;
    if (r > 1)
        danger += a.numberOfRatsAt(r-1,c);
    if (r < a.rows())
        danger += a.numberOfRatsAt(r+1,c);
    if (c > 1)
        danger += a.numberOfRatsAt(r,c-1);
    if (c < a.cols())
        danger += a.numberOfRatsAt(r,c+1);
    
    return danger;
}

// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should drop a poison pellet and not
// move; otherwise, this function sets bestDir to the recommended
// direction to move and returns true.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    // How dangerous is it to stand?
    int standDanger = computeDanger(a, r, c);
    
    // if it's not safe, see if moving is safer
    if (standDanger > 0)
    {
        int bestMoveDanger = standDanger;
        int bestMoveDir = NORTH;  // arbitrary initialization
        
        // check the four directions to see if any move is
        // better than standing, and if so, record the best
        for (int dir = 0; dir < NUMDIRS; dir++)
        {
            int rnew = r;
            int cnew = c;
            if (attemptMove(a, dir, rnew, cnew))
            {
                int danger = computeDanger(a, rnew, cnew);
                if (danger < bestMoveDanger)
                {
                    bestMoveDanger = danger;
                    bestMoveDir = dir;
                }
            }
        }
        
        // if moving is better than standing, recommend move
        if (bestMoveDanger < standDanger)
        {
            bestDir = bestMoveDir;
            return true;
        }
    }
    return false;  // recommend standing
}*/

bool decodeDirection(char ch, int& dir)
{
    switch (tolower(ch))
    {
        default:  return false;
        case 'n': dir = NORTH; break;
        case 'e': dir = EAST;  break;
        case 's': dir = SOUTH; break;
        case 'w': dir = WEST;  break;
    }
    return true;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/x/h or nothing): ";
        string playerMove;
        getline(cin, playerMove);
        
        Player* player = m_arena->player();
        int dir;
        
        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->dropPoisonPellet();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'x')
                return player->dropPoisonPellet();
            else if (playerMove[0] == 'h')
            {
                m_arena->history().display();
                cout << "Press enter to continue." << endl;
                cin.ignore(10000,'\n');
                m_arena->display("");
                continue;
            }
            else if (decodeDirection(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/x/h." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    while ( ! m_arena->player()->isDead()  &&  m_arena->ratCount() > 0)
    {
        string msg = takePlayerTurn();
        Player* player = m_arena->player();
        if (player->isDead())
        {
            cout << msg << endl;
            break;
        }
        m_arena->moveRats();
        m_arena->display(msg);
    }
    if (m_arena->player()->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

// Runs the game automatically to test the recommendMove AI performance!
void Game::autorun(int* turns, int* rats)
{
    int m_turns = 0;
    while(!m_arena->player()->isDead()  &&  m_arena->ratCount() > 0)
    {
        Player* player = m_arena->player();
        
        int dir;
        if (recommendMove(*m_arena, player->row(), player->col(), dir))
            player->move(dir);
        else
            player->dropPoisonPellet();
        
        m_arena->moveRats();
        m_turns++;
    }
    
    *turns = m_turns;
    *rats = m_arena->ratCount();
}
