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
    MyMap<GeoCoord, vector<StreetSegment*>> m_map;
    vector<StreetSegment*> m_segPtrs;
    void processCoord(GeoCoord gc, StreetSegment* seg);
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
    size_t size = m_segPtrs.size();
    for (size_t i = 0; i < size; i++)
        delete m_segPtrs[i];
}

void SegmentMapperImpl::processCoord(GeoCoord gc, StreetSegment* seg)
{
    vector<StreetSegment*>* vecPtr = m_map.find(gc);
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
        StreetSegment* segPtr = new StreetSegment(seg);
        m_segPtrs.push_back(segPtr);
        processCoord(seg.segment.start, segPtr);
        processCoord(seg.segment.end, segPtr);
        for (size_t j = 0; j < seg.attractions.size(); j++)
        {
            GeoCoord attCoord = seg.attractions[j].geocoordinates;
            if (!(attCoord == seg.segment.start || attCoord == seg.segment.end))
                processCoord(attCoord, segPtr);
        }
    }
}

vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
    vector<StreetSegment> segment;
    const vector<StreetSegment*>* vecPtr = m_map.find(gc);
    if (vecPtr != nullptr)
    {
        for (size_t i = 0; i < vecPtr->size(); i++)
            segment.push_back(*(*vecPtr)[i]);
    }
    return segment;
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
