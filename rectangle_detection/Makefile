# rectangle_detection makefile

CC		= g++
CFLAGS	= `pkg-config opencv --cflags`
LIBS 	= `pkg-config opencv --libs`

rectangle_detection.out : rectangle_detection.cpp
	g++ -o rectangle_detection rectangle_detection.cpp hough_line_transform.cpp search_node.cpp segment.cpp intersect.cpp $(CFLAGS) $(LIBS)

clean: 
	rm *.out *.h~ *.cpp~
	echo Clean done
 
