//
//  main.cpp
//  Homework_1
//
//  Created by Runjia Li on 1/19/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include "newSequence.h"
using namespace std;

/*void testSequence()
{
    // Custom tests
    
    Sequence s;
    assert(s.empty());
    assert(!s.insert(1, "LULUL"));  // Inserting at invalid position
    assert(!s.insert(2, "elegiggle")); // Inserting at invalid position
    assert(s.insert(0, "keepo"));
    assert(s.insert(1, "WutFace"));
    assert(s.insert(1, "LUL"));
    assert(s.size() == 3);
    string str;
    assert(s.get(2, str) && str == "WutFace");
    assert(!s.get(3, str));
    assert(s.insert("kappa") == 0);
    assert(s.size() == 4);
    assert(s.get(0, str) && str == "kappa");
    assert(s.erase(3));
    assert(!s.erase(4)); //Invalid position
    assert(s.remove("WutFace") == 0);
    s.insert(2, "kappa");
    assert(s.find("kappa") == 0);
    assert(s.remove("kappa") == 2);
    assert(s.size() == 2);
    assert(s.find("keepo") == 0);
    assert(s.find("meepo") == -1);
    
    Sequence k;
    k.insert(0, "babyrage");
    k.insert(1, "pogchamp");
    k.insert(2, "osfrog");
    
    s.swap(k);
    assert(!k.get(2, str)); // Invalid position
    assert(k.get(1, str) && str == "LUL");
    assert(s.get(1, str) && str == "pogchamp");
    
    Sequence j;
    j.insert(0, "da");
    j.insert(1, "re");
    j.insert(2, "ds");
    
    s.swap(j);
    assert(j.size() == 3);
    assert(s.get(2, str) && str == "ds");
    
    // Pressure tests
    
    Sequence p;
    Sequence q;
    p.swap(q);
    assert(p.size() == 0 && q.size() == 0);
    assert(!p.erase(0)); // Nothing at pos 0
    assert(!p.remove("zero")); // No value of "zero" found
    
    for (int i = 0; i <= 200; i++)
    {
        p.insert(i, "number");
    }
    
    assert(p.size() == 200);
    assert(p.insert("overload") == -1);
    assert(!p.insert(201, "overcharge")); // Inserting out of bounds
    assert(p.erase(199));
    assert(p.size() == 199);
    p.swap(q);
    assert(p.size() == 0 && q.size() == 199);
    
    // Given tests

    Sequence l;
    l.insert(0, "dosa");
    l.insert(1, "pita");
    l.insert(2, "");
    l.insert(3, "matzo");
    assert(l.find("") == 2);
    l.remove("dosa");
    assert(l.size() == 3  &&  l.find("pita") == 0  &&  l.find("") == 1  &&
           l.find("matzo") == 2);
    
    Sequence s1;
    s1.insert(0, "paratha");
    s1.insert(0, "focaccia");
    Sequence s2;
    s2.insert(0, "roti");
    s1.swap(s2);
    assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  &&
           s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);
    
    Sequence s3;
    s3.insert(0, "a");
    s3.insert(1, "b");
    s3.insert(2, "c");
    s3.insert(3, "b");
    s3.insert(4, "e");
    assert(s3.remove("b") == 2);
    assert(s3.size() == 3);
    string x;
    assert(s3.get(0, x)  &&  x == "a");
    assert(s3.get(1, x)  &&  x == "c");
    assert(s3.get(2, x)  &&  x == "e");
    assert(!s3.get(3, x));
    
    cout << "All tests passed." << endl;

}*/

void testScoreList()
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

void testnewSequence()
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

int main()
{
    //testSequence();
    testScoreList();
    testnewSequence();
}
