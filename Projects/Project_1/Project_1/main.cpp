//
//  main.cpp
//  Project_1
//
//  Created by Runjia Li on 1/9/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

/*#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>*/
#include <iostream>
#include "Game.h"
using namespace std;


///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 5, 2);
    //Game g(10, 12, 40);
        
    // Play the game
    //g.play();
    const int reruns = 3000;
    int rats[reruns];
    int turns[reruns];
    int* ratPtr = rats;
    int* turnPtr = turns;
    
    for (int i = 0; i < reruns; i++)
    {
        Game g(10, 12, 40);
        g.autorun(turnPtr, ratPtr);
        ratPtr++;
        turnPtr++;
    }
    
    int ratSum = 0;
    int turnSum = 0;
    int minRat = rats[0];
    int maxTurn = turns[0];
    int wins = 0.0;
    
    
    for (int j = 0; j < reruns; j++)
    {
        if (rats[j] <= minRat)
            minRat = rats[j];
        
        if (turns[j] >= maxTurn)
            maxTurn = turns[j];
        
        ratSum += rats[j];
        turnSum += turns[j];
        if (rats[j] == 0)
        {
            //cout << "Wins in " << turns[j] << " steps." << endl;
            wins++;
        }
    }
    
    cout << reruns << " games played." << endl;
    cout << "Wins: " << wins <<  endl;
    cout << "Most rats slain: " << 40 - minRat << endl;
    cout << "Most turns survived: " << maxTurn << endl;
    cout << "Average rats slain: " << 40 - ratSum / reruns << endl;
    cout << "Average turns survived: "<< turnSum / reruns << endl;
}
