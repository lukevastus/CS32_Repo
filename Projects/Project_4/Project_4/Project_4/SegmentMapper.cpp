#include <vector>
#include "provided.h"
#include "MyMap.h"
using namespace std;

class SegmentMapperImpl
{
public:
	SegmentMapperImpl();
	~SegmentMapperImpl();
	void init(const MapLoader& ml);
	vector<StreetSegment> getSegments(const GeoCoord& gc) const;
private:
    MyMap<GeoCoord, vector<StreetSegment>> m_map;
    void processCoord(GeoCoord gc, StreetSegment seg);
};

bool operator< (const GeoCoord& g1, const GeoCoord& g2)
{
    return (g1.latitude < g2.latitude && g1.longitude < g2.longitude);
}

bool operator== (const GeoCoord& g1, const GeoCoord& g2)
{
    return (g1.latitudeText == g2.latitudeText && g1.longitudeText == g2.longitudeText);
}

SegmentMapperImpl::SegmentMapperImpl()
{
    
}

SegmentMapperImpl::~SegmentMapperImpl()
{
    
}

void SegmentMapperImpl::processCoord(GeoCoord gc, StreetSegment seg)
{
    vector<StreetSegment>* vecPtr = m_map.find(gc);
    if (vecPtr != nullptr)
        vecPtr->push_back(seg);
    else m_map.associate(gc, {seg});
}

void SegmentMapperImpl::init(const MapLoader& ml)
{
    for (size_t i = 0; i < ml.getNumSegments(); i++)
    {
        StreetSegment seg;
        ml.getSegment(i, seg);
        processCoord(seg.segment.start, seg);
        processCoord(seg.segment.end, seg);
        for (size_t j = 0; j < seg.attractions.size(); j++)
            processCoord(seg.attractions[j].geocoordinates, seg);
    }
}

vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
	return *m_map.find(gc);  // This compiles, but may not be correct
}

//******************** SegmentMapper functions ********************************

// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
	m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
	delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
	return m_impl->getSegments(gc);
}
