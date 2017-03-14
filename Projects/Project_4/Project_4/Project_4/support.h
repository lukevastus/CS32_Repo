//
//  support.h
//  Project_4
//
//  Created by Runjia Li on 3/11/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#ifndef support_h
#define support_h
#include <vector>
#include "provided.h"

bool operator< (const GeoCoord& g1, const GeoCoord& g2);

bool operator== (const GeoCoord& g1, const GeoCoord& g2);

struct CoordScore
{
    CoordScore(GeoCoord g, double s): gc(g), score(s)
    {
        
    }
    GeoCoord gc;
    double score;
};

class WatchList
{
public:
    WatchList();
    ~WatchList();
    void insert(CoordScore gc);
    bool extract(GeoCoord& gc);
    
    bool empty() const
    {
        return m_list.size() == 0;
    }
    
    double top() const
    {
        return m_list[0].score;
    }
    
private:
    std::vector<CoordScore> m_list;
};

#endif /* support_h */
