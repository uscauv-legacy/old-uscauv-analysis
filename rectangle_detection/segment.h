#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>
#include "cv.h" 
#include "highgui.h"

using namespace std;

class Segment 
{
	private:
		typedef cv::Point Point;
		
		Point endpoint_1_, endpoint_2_;
	
	public:	
		bool operator== (const Segment &) const;
		Point getEndpoint(int) const;
		Segment(Point, Point);
		Segment();
		~Segment();
};

#endif
