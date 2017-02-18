//
//  maze.cpp
//  maze
//
//  Created by Runjia Li on 2/11/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    const char ROAD = '.';
    const char MARKED = 'a';
    
    if (sr == er && sc == ec)
        return true;
    
    maze[sr][sc] = MARKED;
    
    if (maze[sr - 1][sc] == ROAD && pathExists(maze, nRows, nCols, sr - 1, sc, er, ec))
    {
        return true;
    }
    
    if (maze[sr][sc + 1] == ROAD && pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
    {
        return true;
    }
    
    if (maze[sr + 1][sc] == ROAD && pathExists(maze, nRows, nCols, sr + 1, sc, er, ec))
    {
        return true;
    }
    
    if (maze[sr][sc - 1] == ROAD && pathExists(maze, nRows, nCols, sr, sc - 1, er, ec))
    {
        return true;
    }
    
    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}