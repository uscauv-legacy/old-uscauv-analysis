#include "search_node.h"

using namespace std;

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
    
    //if(match_intersect) { printf("Matched intersects. \n"); }
    //else { printf("Intersects not matched! \n"); }
    
    bool match_corners = true;
    if(match_intersect)
    {
    	//printCorners("Corners: ");
		//right.printCorners("Corners to be matched: ");
	    match_corners = (matchCorners(right.getCorners()));
	    //((intersect_ == right.getIntersect()) && (matchCorners(right.getCorners())));
    	//if(match_corners) { printf("Matched corners. \n"); }
     	//else { printf("Corners not matched! \n"); }
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
	{	printf("Corner: %d, %d ", it->getIntersect().x, it->getIntersect().y); }
		
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
		
		printf("Difference from angle: %f \n", differenceFromAngle(angle));
		if(differenceFromAngle(angle) > error)
		{
			return false;	
		}
		
		for(CornersContainer::const_iterator it = corners_.begin(); it != corners_.end(); ++it)
		{
			printf("Difference from angle: %f \n", it->differenceFromAngle(angle));	
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
	else { return false; }
}

bool SearchNode::matchCorners(const CornersContainer &c) const
{
	//printf("Size of corners, corners to be matched: %d, %d \n", (int)corners_.size(), (int)c.size());
	
	if(corners_.size() != c.size())
	{	
		//printf("Size of corners did not match. \n");
		return false;
	}
	
	for(CornersContainer::const_iterator it = corners_.begin(); it != corners_.end(); ++it)
	{
		if(it->getIntersect() == c[it-corners_.begin()].getIntersect()) { continue; }
		else 
		{	
			for(CornersContainer::const_iterator itt = c.begin(); itt != c.end(); ++itt)
			{
				if(it->getIntersect() == itt->getIntersect()) { continue; }
				//TODO: Match corners even if out of order
				//it->print("Corner intersects not matched: ");
				//c[it-corners_.begin()].print("Corner intersects not matched: ");
				return false;
			}
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

bool SearchNode::matchExistingSegments(const Intersect &intersect) const
{
	int count = 0;
	for(CornersContainer::const_iterator it = corners_.begin(); it != corners_.end(); ++it)
	{
		if((it->getLine(1) == intersect.getLine(1)) || (it->getLine(1) == intersect.getLine(2)) ||
		   (it->getLine(2) == intersect.getLine(1)) || (it->getLine(2) == intersect.getLine(2)))
		{
			count++;
		}	
	}
	if(corners_.size() == 1)
	{
		if(count > 0) 	{ return true; }
		else 		  	{ return false; }	
	}
	if(corners_.size() == 2)
	{
		if(count > 1) 	{ return true; }
		else 		  	{ return false; }	
	}
	else if(corners_.size() == 3)
		{
		if(count > 2) 	{ return true; }
		else 		  	{ return false; }	
	}
	else {
		return false;
	}   
}	

SearchNode::IntersectsContainer SearchNode::findValidIntersects(const IntersectsContainer &intersects) const
{	
	IntersectsContainer valid_intersects;
	for(IntersectsContainer::const_iterator it = intersects.begin(); it != intersects.end(); ++it)
	{
		if((it->getLine(1) == intersect_.getLine(1)) || (it->getLine(1) == intersect_.getLine(2)) ||
		   (it->getLine(2) == intersect_.getLine(1)) || (it->getLine(2) == intersect_.getLine(2)))
		{
			if(!(*it == intersect_))
			{ 
				if(!matchIntersectToCorners(*it))
				{
					if(!matchExistingSegments(*it))
					{
						valid_intersects.push_back(*it);
						it->print("Intersect added to valid_intersects: ");
					}
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
