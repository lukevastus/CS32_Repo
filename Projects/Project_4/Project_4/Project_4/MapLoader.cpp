#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "provided.h"
using namespace std;

class MapLoaderImpl
{
public:
	MapLoaderImpl();
	~MapLoaderImpl();
	bool load(string mapFile);
	size_t getNumSegments() const;
	bool getSegment(size_t segNum, StreetSegment& seg) const;
private:
    vector<StreetSegment*> m_segs;
};

MapLoaderImpl::MapLoaderImpl()
{

}

MapLoaderImpl::~MapLoaderImpl()
{
    size_t size = m_segs.size();
    for (size_t i = 0; i < size; i++)
        delete m_segs[i];
}

bool MapLoaderImpl::load(string mapFile)
{
    ifstream infile(mapFile);
    if (!infile)
        return false;
    
    string name;
    while (getline(infile, name))
    {
        string slat, slon, elat, elon;
        getline(infile, slat, ',');
        infile.ignore();
        getline(infile, slon, ' ');
        getline(infile, elat, ',');
        getline(infile, elon);
        GeoSegment gseg(GeoCoord(slat, slon), GeoCoord(elat, elon));
        StreetSegment* seg = new StreetSegment;
        seg->streetName = name;
        seg->segment = gseg;
        int count;
        infile >> count;
        infile.ignore(10000, '\n');
        while (count != 0)
        {
            string attr, alat, alon;
            getline(infile, attr, '|');
            getline(infile, alat, ',');
            infile.ignore();
            getline(infile, alon);
            Attraction at;
            at.name = attr;
            at.geocoordinates = GeoCoord(alat, alon);
            seg->attractions.push_back(at);
            count--;
        }
        m_segs.push_back(seg);
    }
    return true;
}

size_t MapLoaderImpl::getNumSegments() const
{
    return m_segs.size();
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
    if (segNum >= m_segs.size())
        return false;
    
    seg = *(m_segs[segNum]);
	return true;
}

//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
	m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
	delete m_impl;
}

bool MapLoader::load(string mapFile)
{
	return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
	return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
   return m_impl->getSegment(segNum, seg);
}
