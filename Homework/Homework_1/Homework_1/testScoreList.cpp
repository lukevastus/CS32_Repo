//
//  testScoreList.cpp
//  Homework_1
//
//  Created by Runjia Li on 1/22/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include "ScoreList.h"
using namespace std;

int main()
{
    // Testing ScoreList
    
    ScoreList s;
    assert(s.size() == 0);
    assert(s.maximum() == NO_SCORE);
    assert(s.minimum() == NO_SCORE);
    assert(s.add(20));
    assert(!s.add(120));
    
    for (int i = 1; i < 50; i++)
    {
        s.add(i);
    }
    
    assert(s.size() == 50);
    assert(s.remove(20));
    assert(!s.remove(50));
    assert(s.size() == 49);
    
    for (int j = 48; j < 200; j++)
    {
        s.add(50);
    }
    
    assert(s.size() == 200);
    assert(s.maximum() == 50);
    assert(s.minimum() == 1);
    assert(!s.add(20));
    assert(s.remove(50));
    assert(s.size() == 199);
    s.remove(1);
    assert(s.minimum() == 2);
    
    cout << "All tests passed." << endl;

}