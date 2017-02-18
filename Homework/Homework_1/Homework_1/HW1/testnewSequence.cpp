//
//  testnewSequence.cpp
//  Homework_1
//
//  Created by Runjia Li on 1/22/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include "newSequence.h"
using namespace std;

int main()
{
    // Given test
    
    Sequence a(1000);   // a can hold at most 1000 items
    Sequence b(5);      // b can hold at most 5 items
    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 123;
    
    // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(k, v));
    
    // Failure if we try to insert a sixth item into b
    assert(!b.insert(5, v));
    
    // When two Sequences' contents are swapped, their capacities are
    // swapped as well:
    a.swap(b);
    assert(!a.insert(5, v));
    for (int k = 0; k < 1000; k++)
        assert(b.insert(k, v));
    
    // Generic test
    Sequence s;
    assert(s.insert(0, 10));
    assert(s.insert(0, 20));
    assert(s.size() == 2);
    ItemType x = 999;
    assert(s.get(0, x) && x == 20);
    assert(s.get(1, x) && x == 10);
    
    // Copy constructor
    Sequence d(b);
    assert(d.size() == 1000);
    ItemType z = 0;
    assert(d.get(555, z) && z == 123);
    
    // Assignment operator
    a = d;
    assert(a.size() == 1000);
    ItemType y = 0;
    assert(a.get(322, y) && y == 123);
    
    cout << "All tests passed." << endl;
}