#include "segment.h"

using namespace std;

bool Segment::operator== (const Segment &right) const
{
    return (((endpoint_1_ == right.getEndpoint(1))  || 
    		 (endpoint_1_ == right.getEndpoint(2))) &&
            ((endpoint_2_ == right.getEndpoint(1))  ||
           	 (endpoint_2_ == right.getEndpoint(2))));
}

Segment::Point Segment::getEndpoint(int num) const
{
	if(num == 1) return endpoint_1_;
	
	else return endpoint_2_;
}

Segment::Segment(Point p1, Point p2)
{
	endpoint_1_ = p1;
	endpoint_2_ = p2;
}

Segment::Segment(){}

Segment::~Segment(){}

