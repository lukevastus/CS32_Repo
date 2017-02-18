//
//  testSequence.cpp
//  Homework_1
//
//  Created by Runjia Li on 1/22/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include "Sequence.h"
using namespace std;

int main()
{
    // Custom tests
    
    Sequence s;
    assert(s.empty());
    assert(!s.insert(-1, 7));  // Inserting at invalid position
    assert(!s.insert(2, 71)); // Inserting at invalid position
    assert(s.insert(0, 322));
    assert(s.insert(1, 644));
    assert(s.insert(1, 966));
    assert(s.size() == 3);
    ItemType str = 0;
    assert(s.get(2, str) && str == 644);
    assert(!s.get(3, str));
    assert(s.insert(47) == 0);
    assert(s.size() == 4);
    assert(s.get(0, str) && str == 47);
    assert(s.erase(3));
    assert(!s.erase(4)); //Invalid position
    assert(s.remove(644) == 0);
    s.insert(2, 47);
    assert(s.find(47) == 0);
    assert(s.remove(47) == 2);
    assert(s.size() == 2);
    assert(s.find(322) == 0);
    assert(s.find(33) == -1);
    
    Sequence k;
    k.insert(0, 711);
    k.insert(1, 110);
    k.insert(2, 700);
    
    s.swap(k);
    assert(!k.get(2, str)); // Invalid position
    assert(k.get(1, str) && str == 966);
    assert(s.get(1, str) && str == 110);
    
    Sequence j;
    j.insert(0, 21);
    j.insert(1, 12);
    j.insert(2, 9);
    
    s.swap(j);
    assert(j.size() == 3);
    assert(s.get(2, str) && str == 9);
    
    // Pressure tests
    
    Sequence p;
    Sequence q;
    p.swap(q);
    assert(p.size() == 0 && q.size() == 0);
    assert(!p.erase(0)); // Nothing at pos 0
    assert(!p.remove(38)); // No value of found
    
    for (int i = 0; i <= 200; i++)
    {
        p.insert(i, 11);
    }
    
    assert(p.size() == 200);
    assert(p.insert(12) == -1);
    assert(!p.insert(201, 122)); // Inserting out of bounds
    assert(p.erase(199));
    assert(p.size() == 199);
    p.swap(q);
    assert(p.size() == 0 && q.size() == 199);
    
    // Given tests
    
    Sequence t;
    assert(t.insert(0, 10));
    assert(t.insert(0, 20));
    assert(t.size() == 2);
    ItemType n = 999;
    assert(t.get(0, n) && n == 20);
    assert(t.get(1, n) && n == 10);

    cout << "All tests passed." << endl;
}