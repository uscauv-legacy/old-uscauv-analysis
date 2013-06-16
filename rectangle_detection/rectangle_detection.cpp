#include "search_node.h"
#include "hough_line_transform.h"

using namespace std;

// TODO: Make rectangle_detection a class

// Allow debug statements to be turned on and off
bool debug_statements = false;

#define RED Scalar(0,0,255)
#define BLUE Scalar(255,0,0)
#define GREEN Scalar(0,255,0)
#define WHITE Scalar(255,255,255)

typedef vector<SearchNode> SearchNodeContainer;
typedef vector<SearchNode> SuccessorNodeContainer;
typedef vector<SearchNode> OpenNodeContainer;
typedef vector<SearchNode> ClosedNodeContainer;
typedef vector<SearchNode> RectangleContainer;
typedef vector<Intersect> IntersectsContainer;
typedef cv::Mat Mat;
typedef cv::Scalar Scalar;

void addIntersectsToOpenNodes(OpenNodeContainer &, const IntersectsContainer &, const IntersectsContainer &);
bool matchNodes(const SearchNode &, const SearchNodeContainer &);
void addSuccessorsToOpenList(const SuccessorNodeContainer &, OpenNodeContainer &, ClosedNodeContainer &);
void expandNode(SearchNode, const IntersectsContainer &, SuccessorNodeContainer &);
SearchNode nextNode(OpenNodeContainer &, int &, double);
void drawDetectedRectangles(const RectangleContainer &, Mat &);

int main(int argc, char** argv)
{
	Mat image_src_, image_dst_;
	double theta_, theta_error_;
	int index_ = 0;
	
	if(argc < 4)
	{ 
		fprintf(stderr, "ERROR: Must specify input filename, search theta, and theta error.");
		return 0;
	}
	else if(argc == 5)
	{
		string str(argv[4]);
		if(str.compare("debug") == 0)
			debug_statements = true;
	}
	
	
	// Read in args
	image_src_ = cv::imread(argv[1], 0);	
	theta_ = atof(argv[2]);
	theta_error_ = atof(argv[3]);
	
	if(image_src_.empty())
	{
		fprintf(stderr, "ERROR: Cannot open image file.");
		return 0;
	}
	
	HoughLineTransform transform_(image_src_);
	transform_.applyHoughLineTransform();
	imshow("Hough Lines", transform_.getImageDstColor());
	cv::waitKey(0);
	
	if(transform_.getIntersectsSize() >= 4) 
	{
	
		// Data
		SuccessorNodeContainer successor_nodes_; 
		OpenNodeContainer open_nodes_;
		ClosedNodeContainer closed_nodes_;
		RectangleContainer rectangles_;
	
		IntersectsContainer initial_intersect_;
		
		SearchNode initial_node_(transform_.getIntersects(0), initial_intersect_);
		
		SearchNode search_node_ = initial_node_;
		open_nodes_.push_back(search_node_);
		addIntersectsToOpenNodes(open_nodes_, transform_.getIntersects(), initial_intersect_);
		
		// Find a solution using manhattan distance
		// While there are unexpanded nodes:
		while(!open_nodes_.empty()){
			open_nodes_.erase(open_nodes_.begin() + index_);
			if(debug_statements) printf("Number of nodes in open_nodes: %d \n", open_nodes_.size());	
			
			//if(open_nodes_.size() > 20) break;
		
			// Expand (find the successors of) the current node
			expandNode(search_node_, transform_.getIntersects(), successor_nodes_);
			if(debug_statements) printf("Node expanded.\n");
			
			// Add the successors to the open list
			addSuccessorsToOpenList(successor_nodes_, open_nodes_, closed_nodes_);
			if(debug_statements) printf("Successors added to open list.\n");
			
			// Move the current node (the one just expanded) to the closed list
			closed_nodes_.push_back(search_node_);
			if(debug_statements) printf("Current node closed.\n");
			
			// Pick a new node with theta nearest 90 degrees to expand next
			search_node_ = nextNode(open_nodes_, index_, theta_);
			if(debug_statements) printf("New node found.\n");
			
			// If the new node is the goal state, store it
			if(search_node_.isRectangle(theta_error_, theta_))
			{
				search_node_.addIntersectToCorners();
				rectangles_.push_back(search_node_);
				if(rectangles_.size() > 0) break;
			}
			
			if(debug_statements) printf("-------------------------------------------\n");
		}
		
		if(debug_statements) printf("Number of rectangles detected: %d \n", rectangles_.size());
	
		//imshow("Source", transform.image_src);
		imshow("Hough Lines", transform_.getImageDstColor());
		
		image_dst_ = transform_.getImageDstColor();
		drawDetectedRectangles(rectangles_, image_dst_);
		imshow("Rectangles", image_dst_);	
		cv::waitKey(0);
	
		return 0;
	}
	else { printf("Not enough intersections detected. \n"); }
}

void addIntersectsToOpenNodes(OpenNodeContainer &open_nodes, const IntersectsContainer &intersects, const IntersectsContainer &initial_intersect)
{
	for(IntersectsContainer::const_iterator it = (intersects.begin() + 1); it != intersects.end(); ++it)
	{ 
		SearchNode initial_node(*it, initial_intersect); 
		open_nodes.push_back(initial_node);
	}
}

// Compare successor node to all closed or open nodes
bool matchNodes(const SearchNode &successor, const SearchNodeContainer &nodes)
{
	if(debug_statements) successor.getIntersect().print("Matching nodes to: ");
	for(SearchNodeContainer::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		//if(debug_statements) it->getIntersect().print("Node to match: ");
	
		if(successor == *it)
		{		
			if(debug_statements) printf("Nodes matched! \n");
			return true;
		}
	}
	return false;
}

// Adds list of successor nodes to open nodes
void addSuccessorsToOpenList(const SuccessorNodeContainer &successor_nodes, OpenNodeContainer &open_nodes, ClosedNodeContainer &closed_nodes)
{
	for(SuccessorNodeContainer::const_iterator it = successor_nodes.begin(); it != successor_nodes.end(); ++it)
	{		
		if((!matchNodes(*it, closed_nodes)) &&	
		   (!matchNodes(*it, open_nodes)))
		{
			if(debug_statements) printf("Pushing back successor: ");
			it->getIntersect().print("");
			open_nodes.push_back(*it);
		}
	}
}

// Expand a node
void expandNode(SearchNode search, const IntersectsContainer &intersects, SuccessorNodeContainer &successor_nodes)
{
	if(debug_statements) search.getIntersect().print("Expanding node: ");
	search.printCorners("");
	successor_nodes.clear();
	IntersectsContainer valid_intersects = search.findValidIntersects(intersects);
	if(debug_statements) printf("Number of valid intersect successors: %d \n", valid_intersects.size());
	for(IntersectsContainer::iterator it = valid_intersects.begin(); it != valid_intersects.end(); ++it)
	{
		SearchNode node(*it, search.getCorners());
		node.addToCorners(search.getIntersect());
		successor_nodes.push_back(node);
	}
}

// Determines the next node to expand using value of theta
SearchNode nextNode(OpenNodeContainer &open_nodes, int &index, double theta)
{
	index = 0;
	for(OpenNodeContainer::iterator it = open_nodes.begin(); it != open_nodes.end(); ++it)
	{
		if((it->differenceFromAngle(theta) + it->getCornersSize()) <
		   (open_nodes[index].differenceFromAngle(theta)) + open_nodes[index].getCornersSize())
		{
			index = (it - open_nodes.begin());
		}
	}
	SearchNode return_node = open_nodes[index];
	return return_node;
}	

// Draw detected rectangles on image
void drawDetectedRectangles(const RectangleContainer &rectangles, Mat &image)
{
	int ii = 0;
	for(RectangleContainer::const_iterator it = (rectangles.begin()++); it != rectangles.end(); ++it)
	{
		if(debug_statements) it->printCorners("");
		for(int i = 0; i < 4; i++)
		{
			if(i < 3) { ii = (i + 1); }
			else { ii = 0; }
			
			//if(debug_statements) 
			printf("Drawing edge: %d \n", i);
			it->getCorners(i).print("");
			
			line(image, it->getCorners(i).getIntersect(), it->getCorners(ii).getIntersect(), GREEN, 3, CV_AA);
			circle(image, it->getCorners(i).getIntersect(), 3, WHITE, -1, 8, 0);
		}
	}
}
