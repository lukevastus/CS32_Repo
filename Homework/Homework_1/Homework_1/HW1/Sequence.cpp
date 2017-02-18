//
//  Sequence.cpp
//  Homework_1
//
//  Created by Runjia Li on 1/19/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include <string>
#include "Sequence.h"
using namespace std;

Sequence::Sequence():itemsNum(0)
{
    
}

bool Sequence::empty() const
{
    if (itemsNum == 0)
        return true;
    return false;
}

int Sequence::size() const
{
    return itemsNum;
}

bool Sequence::insert(int pos, const ItemType& value)
{
    if (0 <= pos && pos <= size() && size() < DEFAULT_MAX_ITEMS)
    {
        for (int i = size() - 1; i >= pos; i--)
        {
            items[i + 1] = items[i];
        }
        
        items[pos] = value;
        itemsNum++;
        return true;
    }
    return false;
}

int Sequence::insert(const ItemType& value)
{
    if (size() == DEFAULT_MAX_ITEMS)
        return -1;
    
    for (int i = 0; i < size(); i++)
    {
        if (value <= items[i])
        {
            insert(i, value);
            return i;
        }
    }
    
    insert(size(), value);
    return size();
}

bool Sequence::erase(int pos)
{
    if (0 <= pos && pos < size())
    {
        if (pos == DEFAULT_MAX_ITEMS - 1)
        {
            itemsNum--;
            return true;
        }
        
        for (int i = pos; i < size() - 1; i++)
        {
            items[i] = items[i + 1];
        }
        itemsNum--;
        return true;
    }
    
    return false;
}

int Sequence::remove(const ItemType& value)
{
    int counter = 0;
    for (int i = 0; i < size(); i++)
    {
        if (items[i] == value)
        {
            erase(i);
            counter++;
        }
    }
    return counter;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (0 <= pos && pos < size())
    {
        value = items[pos];
        return true;
    }
    
    return false;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (0 <= pos && pos < size())
    {
        items[pos] = value;
        return true;
    }
    
    return false;
}

int Sequence::find(const ItemType& value) const
{
    int p = -1;
    for (int i = 0; i < size(); i++)
    {
        if (items[i] == value)
        {
            p = i;
            break;
        }
    }
    
    return p;
}

void Sequence::swap(Sequence& other)
{
    Sequence* longer = size() > other.size() ? this : &other;
    Sequence* shorter = size() > other.size() ? &other : this;
    int shortSize = shorter->size();
    
    for (int i = 0; i < shortSize; i++)
    {
        ItemType temp;
        other.get(i, temp);
        other.set(i, items[i]);
        items[i] = temp;
    }
    
    while(longer->size() > shortSize)
    {
        ItemType temp;
        longer->get(shortSize, temp);
        shorter->insert(shorter->size(), temp);
        longer->erase(shortSize);
    }
}











