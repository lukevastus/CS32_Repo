//
//  History.cpp
//  Project_1
//
//  Created by Runjia Li on 1/10/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include "History.h"
#include "globals.h"
using namespace std;


// The constructor initializes a History object that corresponds
// to an Arena with nRows rows and nCols columns.
// You may assume (i.e., you do not have to check) that
// it will be called with a first argument that does not
// exceed MAXROWS and a second that does not exceed MAXCOLS,
// and that neither argument will be less than 1.
History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for (int r = 1; r <= m_rows; r++)
    {
        for (int c = 1; c <= m_cols; c++)
        {
            m_grid[r][c] = 0;
        }
    }
}

// The record function is to be called to notify the History object that
// an unpoisoned rat has eaten a poison pellet at a grid point.
// The function returns false if row r, column c is not within bounds;
// otherwise, it returns true after recording what it needs to.
// This function expects its parameters to be expressed in the same
// coordinate system as the arena
// (e.g., row 1, column 1 is the upper-left-most position).
bool History::record(int r, int c)
{
    if (r <= 0 || c <= 0 || r > m_rows || c > m_cols)
    {
        return false;
    }
    m_grid[r][c]++;
    return true;
}

// The display function clears the screen and displays the history grid
// as the posted programs do. This function does clear the screen
// and write an empty line after the history grid;
// it does not print the Press enter to continue. after the display.
void History::display() const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    clearScreen();
    
    for (r = 1; r <= m_rows; r++)
    {
        for (c = 1; c <= m_cols; c++)
        {
            if (m_grid[r][c] == 0)
            {
                displayGrid[r-1][c-1] = '.';
            }
            else
            {
                displayGrid[r-1][c-1] = (m_grid[r][c] < 26 ? ('A' + m_grid[r][c] - 1) : 'Z');
            }
        }
    }
    
    for (r = 1; r <= m_rows; r++)
    {
        for (c = 1; c <= m_cols; c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
}
