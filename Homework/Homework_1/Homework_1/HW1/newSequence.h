//
//  newSequence.h
//  Homework_1
//
//  Created by Runjia Li on 1/20/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#ifndef newSequence_h
#define newSequence_h
#include <string>

typedef unsigned long ItemType;
const int DEFAULT_MAX_ITEMS = 200;

class Sequence
{
public:
    Sequence(int size);
    Sequence();
    Sequence(const Sequence& other);
    ~Sequence();
    
    Sequence& operator=(const Sequence& other);
    
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    
private:
    ItemType* items;
    int itemsNum;
    int maxSize;
};


#endif /* newSequence_h */
