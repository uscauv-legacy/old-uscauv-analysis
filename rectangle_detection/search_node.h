#ifndef SEARCH_NODE_H
#define SEARCH_NODE_H

#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h> 
#include <iostream>
#include <math.h>
#include "segment.h"
#include "intersect.h"

using namespace std;

class SearchNode 
{
	private:
		typedef vector<Intersect> CornersContainer;
		typedef vector<Intersect> IntersectsContainer;
		
		Intersect intersect_;
		CornersContainer corners_;
		
	public:
		Intersect getIntersect() const;
		const CornersContainer & getCorners() const;
		Intersect getCorners(int) const;
		int getCornersSize() const;
		void addToCorners(Intersect);
		bool operator== (const SearchNode &) const;
		void addIntersectToCorners();
		void printCorners(string) const;
		double differenceFromAngle(double) const;
		bool isRectangle(double, double) const;
		bool matchCorners(const CornersContainer &) const;
		bool matchIntersectToCorners(const Intersect &) const;
		bool matchExistingSegments(const Intersect &) const;
		IntersectsContainer findValidIntersects(const IntersectsContainer &) const;
		SearchNode(Intersect, CornersContainer);
		SearchNode();		
		~SearchNode();
};

#endif
