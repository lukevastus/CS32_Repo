//
//  ScoreList.cpp
//  Homework_1
//
//  Created by Runjia Li on 1/20/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include "ScoreList.h"
#include "Sequence.h"
using namespace std;

ScoreList::ScoreList():scores()
{
    
}

int ScoreList::size() const
{
    return scores.size();
}

bool ScoreList::add(unsigned long score)
{
    if (score <= 100 && size() < DEFAULT_MAX_ITEMS)
    {
        scores.insert(size(), score);
        return true;
    }
    
    return false;
}

bool ScoreList::remove(unsigned long score)
{
    int i = scores.find(score);
    if (i != -1)
    {
        scores.erase(i);
        return true;
    }
    
    return false;
}

unsigned long ScoreList::minimum() const
{
    if (size() == 0)
    {
        return NO_SCORE;
    }
    
    unsigned long temp = 0;
    unsigned long min = 0;
    scores.get(0, min);
    
    for (int i = 1; i < size(); i++)
    {
        scores.get(i, temp);
        if (temp < min)
        {
            min = temp;
        }
    }
    
    return min;
}

unsigned long ScoreList::maximum() const
{
    if (size() == 0)
    {
        return NO_SCORE;
    }
    
    unsigned long temp = 0;
    unsigned long max = 0;
    scores.get(0, max);
    
    for (int i = 1; i < size(); i++)
    {
        scores.get(i, temp);
        if (temp > max)
        {
            max = temp;
        }
    }
    
    return max;
}






