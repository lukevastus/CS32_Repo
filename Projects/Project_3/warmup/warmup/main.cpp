//
//  main.cpp
//  warmup
//
//  Created by Runjia Li on 2/16/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

// Remove the odd integers from li.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original list.
void removeOdds(list<int>& li)
{
    list<int>::iterator it;
    it = li.begin();
    while (it != li.end())
    {
        if ((*it) % 2 != 0)
        {
            it = li.erase(it);
        }
        
        else
        {
            it++;
        }
    }
}

// Remove the odd integers from v.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original vector.
void removeOdds(vector<int>& v)
{
    vector<int>::iterator it;
    it = v.begin();
    while (it != v.end())
    {
        if ((*it) % 2 != 0)
        {
            it = v.erase(it);
        }
        
        else
        {
            it++;
        }
    }
    //vector<int> v2(v.begin(), v.end());
    //v2.swap(v);
}

vector<int> destroyedOnes;

class Movie
{
public:
    Movie(int r) : m_rating(r) {}
    ~Movie() { destroyedOnes.push_back(m_rating); }
    int rating() const { return m_rating; }
private:
    int m_rating;
};

// Remove the movies in li with a rating below 50 and destroy them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original list.
void removeBad(list<Movie*>& li)
{
    list<Movie*>::iterator it;
    it = li.begin();
    while (it != li.end())
    {
        if ((*it)->rating() < 50)
        {
            delete (*it);
            it = li.erase(it);
        }
        
        else
        {
            it++;
        }
    }
}

// Remove the movies in v with a rating below 50 and destroy them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original vector.
void removeBad(vector<Movie*>& v)
{
    vector<Movie*>::iterator it;
    it = v.begin();
    while (it != v.end())
    {
        if ((*it)->rating() < 50)
        {
            delete (*it);
            it = v.erase(it);
        }
        
        else
        {
            it++;
        }
    }
}

void test()
{
    int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
    list<Movie*> x;
    for (int k = 0; k < 8; k++)
        x.push_back(new Movie(a[k]));
    assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
    removeBad(x);
    assert(x.size() == 4 && destroyedOnes.size() == 4);
    vector<int> v;
    for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
    {
        Movie* mp = *p;
        v.push_back(mp->rating());
        delete (*p);
    }
    // Aside:  In C++11, the above loop could be
    //     for (auto p = x.begin(); p != x.end(); p++)
    //     {
    //         Movie* mp = *p;
    //         v.push_back(mp->rating());
    //     }
    // or
    //     for (auto p = x.begin(); p != x.end(); p++)
    //     {
    //         auto mp = *p;
    //         v.push_back(mp->rating());
    //     }
    // or
    //     for (Movie* mp : x)
    //         v.push_back(mp->rating());
    // or
    //     for (auto mp : x)
    //         v.push_back(mp->rating());
    sort(v.begin(), v.end());
    int expect[4] = { 70, 80, 85, 90 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
    sort(destroyedOnes.begin(), destroyedOnes.end());
    int expectGone[4] = { 10, 15, 20, 30 };
    for (int k = 0; k < 4; k++)
        assert(destroyedOnes[k] == expectGone[k]);
    
}



void test2()
{
    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
    list<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdds(x);
    assert(x.size() == 4);
    vector<int> v(x.begin(), x.end());  // construct v from x
    sort(v.begin(), v.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
}

void test3()
{
    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
    vector<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdds(x);
    assert(x.size() == 4);
    sort(x.begin(), x.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(x[k] == expect[k]);
}

void test4()
{
    destroyedOnes = vector<int>();
    int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
    vector<Movie*> x;
    for (int k = 0; k < 8; k++)
        x.push_back(new Movie(a[k]));
    assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
    removeBad(x);
    assert(x.size() == 4 && destroyedOnes.size() == 4);
    vector<int> v;
    for (int k = 0; k < 4; k++)
    {
        v.push_back(x[k]->rating());
        delete x[k];
    }
    sort(v.begin(), v.end());
    int expect[4] = { 70, 80, 85, 90 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
    sort(destroyedOnes.begin(), destroyedOnes.end());
    int expectGone[4] = { 10, 15, 20, 30 };
    for (int k = 0; k < 4; k++)
        assert(destroyedOnes[k] == expectGone[k]);
}

int main()
{
    test();
    test2();
    test3();
    test4();
    cout << "Passed" << endl;
}