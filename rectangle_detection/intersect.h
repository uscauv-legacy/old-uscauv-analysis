#ifndef INTERSECT_H
#define INTERSECT_H

#include "cv.h" 
#include "highgui.h"
#include <vector>
#include "segment.h"

using namespace std;

class Intersect
{
	private:
		typedef cv::Point Point;
		
		Point intersect_;
		Segment line_1_, line_2_;
		double theta_;
	
	public:		
		Point getIntersect() const;
		Segment getLine(int) const;
		double getTheta() const;
		void setTheta(double);
		void print(string) const;
		double differenceFromAngle(double) const;
		bool operator== (const Intersect &) const;
		Intersect(Point, Segment, Segment);
		Intersect();
		~Intersect();
};

#endif
