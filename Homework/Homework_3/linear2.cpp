//
//  linear.cpp
//  linear
//
//  Created by Runjia Li on 2/10/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include <cassert>

// bool somePredicate(double x);
bool somePredicate(double x)
{
    return x < 0;
}

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const double a[], int n)
{
    if (n <= 0)
        return true;
    
    return (allTrue(a + 1, n - 1) && somePredicate(a[0]));
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
    if (n <= 0)
        return 0;
    
    return (countFalse(a + 1, n - 1) + !somePredicate(a[0]));
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const double a[], int n)
{
    if (n <= 0)
        return -1;
    
    if (!somePredicate(a[0]))
        return 0;
    
    int b = firstFalse(a + 1, n - 1);
    return (b == -1) ? -1 : (1 + b);
}

// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
    if (n <= 0)
        return -1;
    
    if (n == 1)
        return 0;
    
    int b = indexOfMin(a + 1, n - 1);
    return (a[0] <= a[1 + b]) ? 0 : (1 + b);
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0)
        return true;
    
    if (n2 > n1 || n1 <= 0)
        return false;
    
    if (a1[0] == a2[0])
        return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    
    return includes(a1 + 1, n1 - 1, a2, n2);
}


int main()
{
    double a1[8] = {-2, -3, 5, -1, -2, 6, -3, -9};
    double a2[3] = {-2, -3, -1};
    assert(!allTrue(a1, 8));
    assert(allTrue(a1, 2));
    assert(allTrue(a2, 3));
    
    assert(countFalse(a1, 8) == 2);
    assert(countFalse(a1, 3) == 1);
    assert(countFalse(a1, 2) == 0);
    
    assert(firstFalse(a1, 8) == 2);
    assert(firstFalse(a1, 2) == -1);
    a1[0] = 2;
    assert(firstFalse(a1, 8) == 0);
    a2[2] = 1;
    assert(firstFalse(a2, 3) == 2);
    
    assert(indexOfMin(a1, 8) == 7);
    a1[7] = 3;
    assert(indexOfMin(a1, 8) == 1);
    a1[0] = -6;
    assert(indexOfMin(a1, 3) == 0);
    
    assert(!includes(a1, 8, a2, 3));
    assert(includes(a1, 8, a2, 1));
    a2[0] = -1;
    a2[2] = 3;
    assert(includes(a1, 8, a2, 3));
    assert(!includes(a1, 4, a2, 3));
    double a3[3] = {5, -3, -2};
    assert(!includes(a1, 8, a3, 3));
    std::cout << "YOU SHALL PASS" << std::endl;
}


