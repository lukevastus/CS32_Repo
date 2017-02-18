//
//  main.cpp
//  Project_2
//
//  Created by Runjia Li on 1/25/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include "Sequence.h"
using namespace std;

int main()
{
    Sequence s;                           // Default constructor
    assert(s.empty());                    // Test empty
    assert(!s.erase(0));                  // Nothing to erase for empty sequence
    assert(!s.insert(1, "tortilla"));     // Insertion at invalid position
    assert(s.insert(0, "tortilla"));      // Insertion to empty sequence
    assert(s.insert(0, "lavash"));        // Insertion to the tail
    ItemType a;
    assert(s.get(0, a) && a == "lavash"); // Test get
    assert(s.size() == 2);                // Test size
    assert(s.insert("avocado") == 0);     // Test insert based on size of ItemType
    assert(s.insert("kale") == 1);
    assert(s.insert("wheat") == 4);
    assert(s.size() == 5);
    assert(s.erase(4) && s.size() == 4);  // Erasing the last node
    assert(s.erase(0) && s.size() == 3);  // Erasing the first node
    s.insert(2, "kale");
    s.insert(4, "kale");
    assert(s.find("kale") == 0);          // Test find
    assert(s.find("rice") == -1);         // Test find (nothing found)
    assert(s.set(4, "honey"));            // Test set
    assert(!s.set(5, "bacon"));           // Set at invalid position
    assert(s.get(4, a) && a == "honey");  // Test if set succeeded
    assert(s.remove("kale") == 2);        // Test remove
    assert(s.remove("carrot") == 0);      // Removing a nonexistent value
    
    Sequence t;
    t.insert(0, "sushi");
    t.insert(0, "teriyaki");
    t.insert(0, "miso");
    t.insert(1, "wasabi");
    s.swap(t);                            // Test swap
    assert(s.size() == 4);                // Size should be swapped
    assert(s.get(0, a) && a == "miso");   // Content should be swapped as well
    assert(t.get(2, a) && a == "honey");
    
    Sequence k(s);                        // Copy constructor
    assert(k.size() == 4);                // Size should be the same
    assert(k.get(0, a) && a == "miso");   // Content should also be the same
    s.insert("tempura");
    assert(k.find("tempura") == -1);      // When s is modified, k is unchanged
    
    k = s;                                // Assignment operator
    assert(k.size() == 5);                // Size should be the same
    assert(k.find("tempura") == 1);       // Content should also be the same
    s.remove("sushi");
    assert(k.get(4, a) && a == "sushi");  // When s is modified, k is unchanged
    
    s = s;                                // Assigning a sequence to itself
    s.swap(s);                            // Swapping with itself
    
    
    // Test subsequence
    
    string a1[8] = {"a", "x", "a", "b", "c", "a", "bs", "da"};
    string a2[3] = {"a", "b", "c"};
    
    Sequence n1, n2;
    for (int i = 0; i < 8; i++)
        n1.insert(i, a1[i]);
    
    for (int i = 0; i < 3; i++)
        n2.insert(i, a2[i]);
    
    string a3[7] = {"a", "b", "c", "a", "b", "c", "a"};
    Sequence n3;
    for (int i = 0; i < 7; i++)
        n3.insert(i, a3[i]);
    
    Sequence n4;
    
    assert(subsequence(n1, n2) == 2);     // Test subsequence
    assert(subsequence(n1, n1) == 0);     // Subsequence of the same instance returns 0
    assert(subsequence(n3, n2) == 0);     // Multiple occurences of seq2
    assert(subsequence(n1, n3) == -1);    // Seq2 is not a subsequence of seq1
    assert(subsequence(n1, n4) == -1);    // Seq2 is empty
    assert(subsequence(n2, n1) == -1);    // Seq2 has larger size than seq1
    
    
    // Test interleave
    
    string a4[5] = {"0", "2", "4", "6", "8"};
    string a5[7] = {"1", "3", "5", "7", "9", "10", "11"};
    
    Sequence n5;
    for (int i = 0; i < 5; i++)
        n4.insert(i, a4[i]);
    for (int i = 0; i < 7; i++)
        n5.insert(i, a5[i]);
    
    interleave(n4, n5, n3);
    assert(n3.size() == 12);              // Test interleave (size of seq2 is larger)
    for (int i = 0; i < 12; i++)
        assert(n3.get(i, a) && a == to_string(i));
    
    n5.erase(6);
    n5.erase(5);
    n4.insert(5, "10");
    n4.insert(6, "11");
    Sequence n9;
    
    interleave(n4, n5, n9);
    assert(n9.size() == 12);              // Test interleave (size of seq1 is larger)
    for (int i = 0; i < 12; i++)
        assert(n9.get(i, a) && a == to_string(i));

    Sequence n6, n7, n8;
    
    interleave(n3, n6, n7);               // Seq2 is empty, result should be a copy of seq1
    interleave(n6, n3, n8);               // Seq1 is empty, result should be a copy of seq2
    for (int i = 0; i < 12; i++)
    {
        assert(n7.get(i, a) && a == to_string(i));
        assert(n8.get(i, a) && a == to_string(i));
    }
    
    interleave(n3, n5, n3);               // Seq1 and result refers to the same sequence
    for (int i = 1; i < 11; i += 2)
        assert(n3.get(i, a) && a == a5[(i - 1) / 2]);
    
    cout << "Passed all tests" << endl;
}
