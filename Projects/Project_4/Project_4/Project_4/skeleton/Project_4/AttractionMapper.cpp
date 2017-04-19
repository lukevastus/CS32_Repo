#include <string>
#include <vector>
#include "provided.h"
#include "MyMap.h"
using namespace std;

class AttractionMapperImpl
{
public:
	AttractionMapperImpl();
	~AttractionMapperImpl();
	void init(const MapLoader& ml);
	bool getGeoCoord(string attraction, GeoCoord& gc) const;
private:
    MyMap<string, GeoCoord> m_map;
};

void convertToLower(string& input)
{
    for (size_t i= 0; i < input.size(); i++)
        input[i] = (input[i] <= 'Z' && input[i] >= 'A') ? (input[i] - ('Z' - 'z')) : input[i];
}

AttractionMapperImpl::AttractionMapperImpl()
{
    
}

AttractionMapperImpl::~AttractionMapperImpl()
{

}

void AttractionMapperImpl::init(const MapLoader& ml)
{
    for (size_t i = 0; i < ml.getNumSegments(); i++)
    {
        StreetSegment seg;
        ml.getSegment(i, seg);
        for (size_t j = 0; j < seg.attractions.size(); j++)
        {
            convertToLower(seg.attractions[j].name);
            m_map.associate(seg.attractions[j].name, seg.attractions[j].geocoordinates);
        }
    }
}

bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const
{
    convertToLower(attraction);
    const GeoCoord* temp = m_map.find(attraction);
    if (temp != nullptr)
    {
        gc = *temp;
        return true;
    }
    return false;
}

//******************** AttractionMapper functions *****************************

// These functions simply delegate to AttractionMapperImpl's functions.
// You probably don't want to change any of this code.

AttractionMapper::AttractionMapper()
{
	m_impl = new AttractionMapperImpl;
}

AttractionMapper::~AttractionMapper()
{
	delete m_impl;
}

void AttractionMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
{
	return m_impl->getGeoCoord(attraction, gc);
}
