//
//  newSequence.cpp
//  Homework_1
//
//  Created by Runjia Li on 1/20/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include <string>
#include "newSequence.h"
using namespace std;

Sequence::Sequence():itemsNum(0), maxSize(DEFAULT_MAX_ITEMS)
{
    items = new ItemType[DEFAULT_MAX_ITEMS];
}

Sequence::Sequence(int size):itemsNum(0), maxSize(size)
{
    items = new ItemType[size];
}

Sequence::Sequence(const Sequence& other):itemsNum(other.itemsNum), maxSize(other.maxSize)
{
    items = new ItemType[other.maxSize];
    for (int i = 0; i < other.itemsNum; i++)
    {
        items[i] = other.items[i];
    }
}

Sequence& Sequence::operator=(const Sequence &other)
{
    if (this == &other)
    {
        return *this;
    }
        
    ItemType* temp = items;
    items = new ItemType[other.maxSize];
    
    itemsNum = other.itemsNum;
    maxSize = other.maxSize;
    
    for (int i = 0; i < other.itemsNum; i++)
    {
        items[i] = other.items[i];
    }
    
    delete[] temp;
    return *this;
}

Sequence::~Sequence()
{
    delete[] items;
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
    if (0 <= pos && pos <= size() && size() < maxSize)
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
    if (size() == maxSize)
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
        if (pos == maxSize - 1)
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
    ItemType* temp = other.items;
    other.items = items;
    items = temp;
    
    int numTemp = other.itemsNum;
    other.itemsNum = itemsNum;
    itemsNum = numTemp;
    
    int maxSizeTemp = other.maxSize;
    other.maxSize = maxSize;
    maxSize = maxSizeTemp;
}





