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
		IntersectsContainer findValidIntersects(const IntersectsContainer &) const;
		SearchNode(Intersect, CornersContainer);
		SearchNode();		
		~SearchNode();
};

Intersect SearchNode::getIntersect() const
{
	return intersect_;
}

const SearchNode::CornersContainer & SearchNode::getCorners() const
{
	return corners_;
}

Intersect SearchNode::getCorners(int index) const
{
	return corners_[index];
}

int SearchNode::getCornersSize() const
{
	return corners_.size();
}

void SearchNode::addToCorners(Intersect i)
{
	corners_.push_back(i);
}

bool SearchNode::operator== (const SearchNode &right) const
{
    bool match_intersect = (intersect_ == right.getIntersect());
    
    if(match_intersect) { printf("Matched intersects. \n"); }
    else { printf("Intersects not matched! \n"); }
    
    bool match_corners = true;
    if(match_intersect)
    {
    	printCorners("Corners: ");
		right.printCorners("Corners to be matched: ");
	    match_corners = (matchCorners(right.getCorners()));
	    //((intersect_ == right.getIntersect()) && (matchCorners(right.getCorners())));
    	if(match_corners) { printf("Matched corners. \n"); }
     	else { printf("Corners not matched! \n"); }
    }
    return (match_intersect && match_corners);
}

void SearchNode::addIntersectToCorners()
{
	corners_.push_back(intersect_);
}

void SearchNode::printCorners(string input) const
{
	printf("%s", input.c_str());
	for(CornersContainer::const_iterator it = corners_.begin(); it != corners_.end(); ++it)
		printf("Corner: %d, %d ", it->getIntersect().x, it->getIntersect().y);
		
	printf("\n");
}

double SearchNode::differenceFromAngle(double angle) const
{
	return abs(angle - intersect_.getTheta());
}

bool SearchNode::isRectangle(double error, double angle) const
{
	if(corners_.size() == 3)
	{
		printf("Node has 4 corners. \n");
		for(CornersContainer::const_iterator it = corners_.begin(); it != corners_.end(); ++it)
		{
			if(it->differenceFromAngle(angle) > error)
			{ 
				printf("Angle of at least one corner is greater than error allowed. \n");
				return false;
			}
		}
		// TODO: calculate area
		printf("Node identified as a rectangle. \n");
		return true;
	}
	else return false;
}

bool SearchNode::matchCorners(const CornersContainer &c) const
{
	printf("Size of corners, corners to be matched: %d, %d \n", (int)corners_.size(), (int)c.size());
	
	if(corners_.size() != c.size())
	{	
		printf("Size of corners did not match. \n");
		return false;
	}
	
	for(CornersContainer::const_iterator it = corners_.begin(); it != corners_.end(); ++it)
	{
		if(!(it->getIntersect() == c[it-corners_.begin()].getIntersect()))
		{
			it->print("Corner intersects not matched: ");
			c[it-corners_.begin()].print("Corner intersects not matched: ");
			return false;
		}
	}
	
	return true;
}

bool SearchNode::matchIntersectToCorners(const Intersect &intersect) const
{
	for(CornersContainer::const_iterator it = corners_.begin(); it != corners_.end(); ++it)
	{	if(intersect == *it) { return true; } }
		
	return false;
}

SearchNode::IntersectsContainer SearchNode::findValidIntersects(const IntersectsContainer &intersects) const
{	
	IntersectsContainer valid_intersects;
	for(IntersectsContainer::const_iterator it = intersects.begin(); it != intersects.end(); ++it)
	{
		if((it->getLine(1) == intersect_.getLine(1)) || (it->getLine(1) == intersect_.getLine(2)) ||
		   (it->getLine(2) == intersect_.getLine(1)) || (it->getLine(2) == intersect_.getLine(2)))
		{
			if(!(*it == intersect_))\
			{
				if(!matchIntersectToCorners(*it))
				{
					valid_intersects.push_back(*it);
					it->print("Intersect added to valid_intersects: ");
				}
			}
		}
	}

	return valid_intersects;
}

SearchNode::SearchNode(Intersect i , CornersContainer c)
{
	intersect_ = i;
	corners_ = c;	
}

SearchNode::SearchNode(){}

SearchNode::~SearchNode(){}

#endif