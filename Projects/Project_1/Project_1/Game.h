//
//  Game.h
//  Project_1
//
//  Created by Runjia Li on 1/9/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#ifndef Game_h
#define Game_h
#include <string>

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRats);
    ~Game();
    
    // Mutators
    void play();
    
    //Automated run
    void autorun(int* turns, int* rats);
    
private:
    Arena* m_arena;
    
    // Helper functions
    std::string takePlayerTurn();
};

#endif /* Game_h */
