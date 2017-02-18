//
//  main.cpp
//  mazequeue
//
//  Created by Runjia Li on 2/4/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Coord class, which represents an (r,c) coordinate pair
class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};


// Return true if there is a path from (sr,sc) to (er,ec)
// Assumptions:
// the maze array contains nRows rows (you couldn't check for this anyway);
// each string in the maze is of length nCols;
// the maze contains only Xs and dots when passed in to the function;
// the top and bottom rows of the maze contain only Xs, as do the left and right columns;
// sr and er are between 0 and nRows-1, and sc and ec are between 0 and nCols-1;
// maze[sr][sc] and maze[er][ec] are '.' (i.e., not walls)

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    // Constants
    const char ROAD = '.';
    const char MARKED = 'a';
    
    queue<Coord> coordQueue;
    coordQueue.push(Coord(sr, sc));
    maze[sr][sc] = MARKED;
    
    while(!coordQueue.empty())
    {
        Coord current = coordQueue.front();
        int r = current.r();
        int c = current.c();
        coordQueue.pop();
        if (r == er && c == ec)
            return true;
        
        if (maze[r - 1][c] == ROAD)
        {
            coordQueue.push(Coord(r - 1, c));
            maze[r - 1][c] = MARKED;
        }
        
        if (maze[r][c + 1] == ROAD)
        {
            coordQueue.push(Coord(r, c + 1));
            maze[r][c + 1] = MARKED;
        }
        
        if (maze[r + 1][c] == ROAD)
        {
            coordQueue.push(Coord(r + 1, c));
            maze[r + 1][c] = MARKED;
        }
        
        if (maze[r][c - 1] == ROAD)
        {
            coordQueue.push(Coord(r, c - 1));
            maze[r][c - 1] = MARKED;
        }
    }
    
    return false;
}



