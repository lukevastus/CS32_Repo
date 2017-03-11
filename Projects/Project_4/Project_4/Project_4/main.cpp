//
//  main.cpp
//  Project_4
//
//  Created by Runjia Li on 3/8/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include "MyMap.h"
#include "provided.h"
using namespace std;

int main()
{
    MyMap<string,double> nameToGPA; // maps student name to GPA
    // add new items to the binary search tree-based map
    assert(nameToGPA.size() == 0);
    nameToGPA.associate("Carey", 3.5); // Carey has a 3.5 GPA
    nameToGPA.associate("David", 3.99); // David beat Carey
    assert(nameToGPA.size() == 2);
    nameToGPA.associate("Abe", 3.2); // Abe has a 3.2 GPA
    
    assert(*(nameToGPA.find("Carey")) == 3.5);
    assert(*(nameToGPA.find("David")) == 3.99);
    assert(*(nameToGPA.find("Abe")) == 3.2);

    double* davidsGPA = nameToGPA.find("David");
    if (davidsGPA != nullptr)
        *davidsGPA = 1.5; // after a re-grade of David’s exam
    
    assert(*(nameToGPA.find("David")) == 1.5);

    nameToGPA.associate("Carey", 4.0); // Carey deserves a 4.0
    // replaces old 3.5 GPA
    
    assert(*(nameToGPA.find("Carey")) == 4.0);
    
    double* lindasGPA = nameToGPA.find("Linda");
    assert(lindasGPA == nullptr);

    if (lindasGPA == nullptr)
        cout << "Linda is not in the roster!" << endl;
    else
        cout << "Linda’s GPA is: " << *lindasGPA << endl;
    
    nameToGPA.clear();
    assert(nameToGPA.size() == 0);
    assert(nameToGPA.find("Carey") == nullptr);
    assert(nameToGPA.find("David") == nullptr);
    assert(nameToGPA.find("Abe") == nullptr);
    
    MapLoader m;
    assert(m.load("/Users/runjiali/Documents/CS32/CS32_Repo/Projects/Project_4/Project_4/Project_4/mapdata.txt"));
    StreetSegment s;
    m.getSegment(4, s);
    assert(s.streetName == "13th Helena Drive" && s.segment.start.longitudeText == "-118.4798135");
    
    AttractionMapper am;
    am.init(m);
    GeoCoord gc;
    assert(am.getGeoCoord("Northwest Campus Auditorium", gc) && gc.latitudeText == "34.0718231");
    assert(am.getGeoCoord("Sproul Landing", gc) && gc.longitudeText == "-118.4505665");

    
    cout << "All tests passed" << endl;
}
