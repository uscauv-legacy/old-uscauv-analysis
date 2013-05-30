#ifndef HOUGH_LINE_TRANSFORM_H
#define HOUGH_LINE_TRANSFORM_H

#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h> 
#include <iostream>
#include <math.h>
#include "segment.h"
#include "intersect.h"

using namespace std;

#define RED Scalar(0,0,255)
#define BLUE Scalar(255,0,0)
#define GREEN Scalar(0,255,0)

class HoughLineTransform 
{
	private:
		typedef vector<cv::Vec2f> LinesContainer;
		typedef vector<Intersect> IntersectsContainer;
		typedef vector<Segment> SegmentsContainer;
		typedef cv::Mat Mat;
		typedef cv::Point Point;
		typedef cv::Scalar Scalar;
		
		Mat image_src_, image_dst_, image_dst_color_;
		LinesContainer lines_;
		IntersectsContainer intersects_;
		SegmentsContainer segments_;
		float rho_, theta_;
		Point point_1_, point_2_, point_A1_, point_A2_, point_B1_, point_B2_, intersect_;
		double a_, b_, x0_, y0_, theta_error_;
	
	public:
		const IntersectsContainer getIntersects() const;
		Intersect getIntersects(int) const;
		int getIntersectsSize() const;
		Mat getImageSrc() const;
		Mat getImageDst() const;
		Mat getImageDstColor() const;
		Segment * findMatchingSegment(Point, Point, SegmentsContainer &);
		int calculateDenominator(Point, Point, Point, Point) const;
		Point calculateIntersect(Point, Point, Point, Point, int) const;
		void calculateTheta(Intersect &);
		bool storeIntersects(Segment &, Segment &, Point);
		void calculateSegments(int);
		void drawDetectedLines(int);
		void calculateIntersections(int);
		void applyHoughLineTransform();
		HoughLineTransform(Mat);
		HoughLineTransform();
		~HoughLineTransform();
};

#endif
