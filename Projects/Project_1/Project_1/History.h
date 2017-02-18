//
//  History.h
//  Project_1
//
//  Created by Runjia Li on 1/10/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#ifndef History_h
#define History_h
#include "globals.h"

class History
{
public:
    // Constructor
    History(int nRows, int nCols);
    
    // Mutators
    bool record(int r, int c);
    void display() const;
    
private:
    int m_grid[MAXROWS][MAXCOLS];
    int m_rows;
    int m_cols;
};

#endif /* History_h */
