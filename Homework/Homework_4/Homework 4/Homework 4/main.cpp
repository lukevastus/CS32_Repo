//
//  main.cpp
//  Homework 4
//
//  Created by Runjia Li on 3/4/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include "Sequence.h"
#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
using namespace std;

void test()
{
    Sequence<int> si;
    Sequence<string> ss;
    assert(ss.empty());
    assert(ss.size() == 0);
    assert(ss.insert("Hello") == 0);
    assert(si.insert(10) == 0);
    assert(si.erase(0));
    assert(ss.remove("Goodbye") == 0);
    assert(ss.find("Hello") == 0);
    string s;
    assert(ss.get(0, s));
    assert(ss.set(0, "Hello"));
    Sequence<string> ss2(ss);
    ss2.swap(ss);
    ss2 = ss;
    assert(subsequence(ss,ss2) == 0);
    assert(subsequence(si,si) == -1);
    interleave(ss,ss2,ss);
    interleave(si,si,si);
    
    Sequence<string> s3;                           // Default constructor
    assert(s3.empty());                    // Test empty
    assert(!s3.erase(0));                  // Nothing to erase for empty sequence
    assert(!s3.insert(1, "tortilla"));     // Insertion at invalid position
    assert(s3.insert(0, "tortilla"));      // Insertion to empty sequence
    assert(s3.insert(0, "lavash"));        // Insertion to the tail
    string a;
    assert(s3.get(0, a) && a == "lavash"); // Test get
    assert(s3.size() == 2);                // Test size
    assert(s3.insert("avocado") == 0);     // Test insert based on size of ItemType
    assert(s3.insert("kale") == 1);
    assert(s3.insert("wheat") == 4);
    assert(s.size() == 5);
    assert(s3.erase(4) && s3.size() == 4);  // Erasing the last node
    assert(s3.erase(0) && s3.size() == 3);  // Erasing the first node
    s3.insert(2, "kale");
    s3.insert(4, "kale");
    assert(s3.find("kale") == 0);          // Test find
    assert(s3.find("rice") == -1);         // Test find (nothing found)
    assert(s3.set(4, "honey"));            // Test set
    assert(!s3.set(5, "bacon"));           // Set at invalid position
    assert(s3.get(4, a) && a == "honey");  // Test if set succeeded
    assert(s3.remove("kale") == 2);        // Test remove
    assert(s3.remove("carrot") == 0);      // Removing a nonexistent value
    
    Sequence<string> t;
    t.insert(0, "sushi");
    t.insert(0, "teriyaki");
    t.insert(0, "miso");
    t.insert(1, "wasabi");
    s3.swap(t);                            // Test swap
    assert(s3.size() == 4);                // Size should be swapped
    assert(s3.get(0, a) && a == "miso");   // Content should be swapped as well
    assert(t.get(2, a) && a == "honey");
    
    Sequence<string> k(s3);                        // Copy constructor
    assert(k.size() == 4);                // Size should be the same
    assert(k.get(0, a) && a == "miso");   // Content should also be the same
    s3.insert("tempura");
    assert(k.find("tempura") == -1);      // When s is modified, k is unchanged
    
    k = s3;                                // Assignment operator
    assert(k.size() == 5);                // Size should be the same
    assert(k.find("tempura") == 1);       // Content should also be the same
    s3.remove("sushi");
    assert(k.get(4, a) && a == "sushi");  // When s is modified, k is unchanged
    
    s3 = s3;                                // Assigning a sequence to itself
    s3.swap(s3);                            // Swapping with itself
    
    
    // Test subsequence
    
    string a1[8] = {"a", "x", "a", "b", "c", "a", "bs", "da"};
    string a2[3] = {"a", "b", "c"};
    
    Sequence<string> n1, n2;
    for (int i = 0; i < 8; i++)
        n1.insert(i, a1[i]);
    
    for (int i = 0; i < 3; i++)
        n2.insert(i, a2[i]);
    
    string a3[7] = {"a", "b", "c", "a", "b", "c", "a"};
    Sequence<string> n3;
    for (int i = 0; i < 7; i++)
        n3.insert(i, a3[i]);
    
    Sequence<string> n4;
    
    assert(subsequence(n1, n2) == 2);     // Test subsequence
    assert(subsequence(n1, n1) == 0);     // Subsequence of the same instance returns 0
    assert(subsequence(n3, n2) == 0);     // Multiple occurences of seq2
    assert(subsequence(n1, n3) == -1);    // Seq2 is not a subsequence of seq1
    assert(subsequence(n1, n4) == -1);    // Seq2 is empty
    assert(subsequence(n2, n1) == -1);    // Seq2 has larger size than seq1
    
    
    // Test interleave
    
    string a4[5] = {"0", "2", "4", "6", "8"};
    string a5[7] = {"1", "3", "5", "7", "9", "10", "11"};
    
    Sequence<string> n5;
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
    Sequence<string> n9;
    
    interleave(n4, n5, n9);
    assert(n9.size() == 12);              // Test interleave (size of seq1 is larger)
    for (int i = 0; i < 12; i++)
        assert(n9.get(i, a) && a == to_string(i));
    
    Sequence<string> n6, n7, n8;
    
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

int main()
{
    test();
}


/*class Complex
{
public:
    Complex(double r = 0, double i = 0)
    :  m_real(r), m_imag(i)
    {}
    double real() const { return m_real; }
    double imag() const { return m_imag; }
private:
    double m_real;
    double m_imag;
};

bool operator> (const Complex& c1, const Complex& c2)
{
    return (pow(c1.real(), 2) + pow(c1.imag(), 2)) > (pow(c2.real(), 2) + pow(c2.imag(), 2));
}

int main()
{
    Sequence<int> si;
    si.insert(50);                 // OK
    Sequence<Complex> sc;
    sc.insert(0, Complex(50,20));  // OK
    sc.insert(Complex(40,10));     // error!
}*/
