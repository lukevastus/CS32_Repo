#include <string>
#include <vector>
#include <stack>
#include <chrono>
#include <iostream>
#include "provided.h"
#include "MyMap.h"
#include "support.h"
using namespace std;

class NavigatorImpl
{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(string start, string end, vector<NavSegment>& directions) const;
private:
    MapLoader m_ml;
    AttractionMapper m_am;
    SegmentMapper m_sm;
    vector<GeoCoord> getNeighbors(const GeoCoord& start) const;
    bool buildRoute(const GeoCoord& current, const MyMap<GeoCoord, GeoCoord>& map, vector<NavSegment>& vec) const;
    bool buildStreet(const GeoCoord& g1, const GeoCoord& g2, StreetSegment& s) const;
};

bool operator== (const StreetSegment& s1, const StreetSegment& s2)
{
    return (s1.streetName == s2.streetName && s1.segment.start == s2.segment.start && s1.segment.end == s2.segment.end);
}

bool isInVector(const GeoCoord& coord, const vector<GeoCoord>& vec)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (vec[i] == coord)
            return true;
    }
    return false;
}

string getDirection(const GeoCoord& g1, const GeoCoord& g2)
{
    GeoSegment gs(g1, g2);
    double angle = angleOfLine(gs);
    if (22.5 < angle && angle <= 67.5)
        return "northeast";
    if (67.5 < angle && angle <= 112.5)
        return "north";
    if (112.5 < angle && angle <= 157.5)
        return "northwest";
    if (157.5 < angle && angle <= 202.5)
        return "west";
    if (202.5 < angle && angle <= 247.5)
        return "southwest";
    if (247.5 < angle && angle <= 292.5)
        return "south";
    if (292.5 < angle && angle <= 337.5)
        return "southeast";
    return "east";
}

string getTurn(const GeoSegment& line1, const GeoSegment& line2)
{
    return angleBetween2Lines(line1, line2) > 180.0 ? "right" : "left";
}

NavigatorImpl::NavigatorImpl()
{
    
}

NavigatorImpl::~NavigatorImpl()
{
    
}

vector<GeoCoord> NavigatorImpl::getNeighbors(const GeoCoord& start) const
{
    vector<GeoCoord> coords;
    vector<StreetSegment> streets = m_sm.getSegments(start);
    for (size_t i = 0; i < streets.size(); i++)
    {
        if (!(start == streets[i].segment.start))
            coords.push_back(streets[i].segment.start);
        if (!(start == streets[i].segment.end))
            coords.push_back(streets[i].segment.end);
        for (size_t j = 0; j < streets[i].attractions.size(); j++)
        {
            if (!(start == streets[i].attractions[j].geocoordinates))
                coords.push_back(streets[i].attractions[j].geocoordinates);
        }
    }
    return coords;
}

bool NavigatorImpl::buildStreet(const GeoCoord& g1, const GeoCoord& g2, StreetSegment& s) const
{
    vector<StreetSegment> segs1, segs2;
    segs1 = m_sm.getSegments(g1);
    segs2 = m_sm.getSegments(g2);
    for (size_t i = 0; i < segs1.size(); i++)
    {
        for (size_t j = 0; j < segs2.size(); j++)
        {
            if (segs1[i] == segs2[j])
            {
                s = segs1[i];
                return true;
            }
             
        }
    }
    return false;
}

bool NavigatorImpl::buildRoute(const GeoCoord& current, const MyMap<GeoCoord, GeoCoord>& map, vector<NavSegment>& vec) const
{
    stack<GeoCoord> coords;
    coords.push(current);
    const GeoCoord* prevCoord = map.find(current);
    // Reproduce the series of GeoCoords from the map
    while (prevCoord != nullptr)
    {
        coords.push(*prevCoord);
        prevCoord = map.find(*prevCoord);
    }
    vector<NavSegment> route;
    // Reproduce NavSegments using the GeoCoords
    while (!coords.empty())
    {
        GeoCoord g1 = coords.top();
        coords.pop();
        if (coords.empty())
            break;
        GeoCoord g2 = coords.top();
        StreetSegment s;
        if (!buildStreet(g1, g2, s))
            return false;
        NavSegment curSeg(getDirection(g1, g2), s.streetName, distanceEarthKM(g1, g2), GeoSegment(g1, g2));
        if (!route.empty())
        {
            NavSegment prevSeg = route[route.size() - 1];
            if (prevSeg.m_streetName != curSeg.m_streetName)
            {
                NavSegment turnSeg(getTurn(prevSeg.m_geoSegment, curSeg.m_geoSegment), curSeg.m_streetName);
                route.push_back(turnSeg);
            }
        }
        route.push_back(curSeg);
    }
    
    vec = route;
    return true;
}

bool NavigatorImpl::loadMapData(string mapFile)
{
    if (!m_ml.load(mapFile))
        return false;
    m_am.init(m_ml);
    m_sm.init(m_ml);
	return true;
}

NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const
{
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

    GeoCoord startCoord, endCoord;
    if (!m_am.getGeoCoord(start, startCoord))
        return NAV_BAD_SOURCE;
    if (!m_am.getGeoCoord(end, endCoord))
        return NAV_BAD_DESTINATION;
    
    MyMap<GeoCoord, double> sScore; // Cost to get to GeoCoord from start
    MyMap<GeoCoord, double> eScore; // sScore + distance from GeoCoord to end
    MyMap<GeoCoord, GeoCoord> prevCoord; // Records where it came from
    MyMap<GeoCoord, bool> isEvaluated; // Records whether a GeoCoord has been visited
    vector<GeoCoord> watchList; // GeoCoords being queued up to get evaluated
    
    sScore.associate(startCoord, 0);
    eScore.associate(startCoord, distanceEarthKM(startCoord, endCoord));
    watchList.push_back(startCoord);
    
    while (!watchList.empty())
    {
        // Find the GeoCoord on watchlist closest to destination
        size_t minIndex = 0;
        double minCost = *eScore.find(watchList[0]);
        for (size_t i = 0; i < watchList.size(); i++)
        {
            double curCost = *eScore.find(watchList[i]);
            minCost = (curCost < minCost) ? curCost : minCost;
            minIndex = (curCost < minCost) ? i : minIndex;
        }
        
        // Build the route when arriving at destination
        if (watchList[minIndex] == endCoord)
        {
            if (!buildRoute(watchList[minIndex], prevCoord, directions))
                return NAV_NO_ROUTE;
            chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
            cout << "Time to find route: " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << "ms" << endl;
            return NAV_SUCCESS;
        }
        
        // Visit and evaluate the GeoCoord selected in previous step
        GeoCoord curCoord = watchList[minIndex];
        watchList.erase(watchList.begin() + minIndex);
        isEvaluated.associate(curCoord, true);
        
        // Push each of its neighbors to the watchlist if they haven't been visited
        vector<GeoCoord> neighbors = getNeighbors(curCoord);
        for (size_t i = 0; i < neighbors.size(); i++)
        {
            if (isEvaluated.find(neighbors[i]) == nullptr)
            {
                double curScore = *sScore.find(curCoord) + distanceEarthKM(curCoord, neighbors[i]);
                if (!isInVector(neighbors[i], watchList))
                    watchList.push_back(neighbors[i]);
                else if (curScore >= *sScore.find(neighbors[i]))
                    // If it costs more to visit the neighbor in the new route, then it is not the best route
                    continue;
                
                prevCoord.associate(neighbors[i], curCoord);
                sScore.associate(neighbors[i], curScore);
                eScore.associate(neighbors[i], curScore + distanceEarthKM(neighbors[i], endCoord));
            }
        }
    }

	return NAV_NO_ROUTE;
}

//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(string start, string end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}
