//
//  support.cpp
//  Project_4
//
//  Created by Runjia Li on 3/11/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include "support.h"
#include "provided.h"
#include <algorithm>

bool operator< (const GeoCoord& g1, const GeoCoord& g2)
{
    return (g1.latitude < g2.latitude && g1.longitude < g2.longitude);
}

bool operator== (const GeoCoord& g1, const GeoCoord& g2)
{
    return (g1.latitudeText == g2.latitudeText && g1.longitudeText == g2.longitudeText);
}

WatchList::WatchList()
{
    
}

WatchList::~WatchList()
{
}

void WatchList::insert(CoordScore gc)
{
    m_list.push_back(gc);
    if (m_list.size() == 1)
        return;
    size_t loc = m_list.size() - 1;
    while (loc > 0)
    {
        if (m_list[loc].score < m_list[(loc - 1) / 2].score)
        {
            std::swap(m_list[loc], m_list[(loc - 1) / 2]);
            loc = (loc - 1) / 2;
            continue;
        }
        break;
    }
}

bool WatchList::extract(GeoCoord& gc)
{
    if (m_list.size() > 0)
    {
        gc = m_list[0].gc;
        if (m_list.size() > 1)
            m_list[0] = m_list[m_list.size() - 1];
        m_list.pop_back();
        size_t loc = 0;
        while ((loc * 2 + 1) <= (m_list.size() - 1))
        {
            size_t target = loc * 2 + 1;
            if ((loc * 2 + 2) <= (m_list.size() - 1))
                target = m_list[loc * 2 + 1].score < m_list[loc * 2 + 2].score ? (loc * 2 + 1) : (loc * 2 + 2);
            if (m_list[target].score < m_list[loc].score)
            {
                std::swap(m_list[loc], m_list[target]);
                loc = target;
                continue;
            }
            break;
        }
        return true;
    }
    return false;
}