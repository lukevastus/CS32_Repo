//
//  support.cpp
//  Project_4
//
//  Created by Runjia Li on 3/11/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include "support.h"
#include "provided.h"

bool operator< (const GeoCoord& g1, const GeoCoord& g2)
{
    return (g1.latitude < g2.latitude && g1.longitude < g2.longitude);
}

bool operator== (const GeoCoord& g1, const GeoCoord& g2)
{
    return (g1.latitudeText == g2.latitudeText && g1.longitudeText == g2.longitudeText);
}

