#ifndef __SEGMENT_HEADER_FILE
#define __SEGMENT_HEADER_FILE

#define NO_INTERSECTION

typedef float coord_type; // I'm skipping the possiblity to implement a rational number class and use it, but that would have been the correct thing to do


//TODO: Do I want to have operator= implementations?

//TODO: This is a hacky solution, do something better
bool IS_ZERO(coord_type val);

class Point {
public:
	coord_type x, y;
	/*
	 Constructor from x,y coords.
	*/
	Point(coord_type x, coord_type y);
	/*
	* Copy constructor.
	*/
	Point(const Point& p);

	/*
		Arithmetic operators, act like 2D vector operations.
	*/
	Point operator-(const Point& p) const;
	Point operator+(const Point& p) const;

	/*
		Comparison operators, p1 < p2 if p1 lies to the left of p2.
		For points with equal 'x' value, return p1 < p2 if p1 is below p2.
	*/
	bool operator<(const Point& p) const;
	bool operator==(const Point& p) const;
};

class Segment {
public:
	Point beg, end;
	/*
		Constructor from two endpoints.
	*/
	Segment(const Point& beg, const Point& end);
	/*
	*	Copy constructor.
	*/
	Segment(const Segment& s);
	/*
		Returns true iff this segment contains the given point within its boundaries.
	*/
	bool contains(const Point& p) const;
	/*
		Check if this segment is parallel to another.
	*/
	bool is_parallel(const Segment& s) const;
	/*
		Check if two segments intersect. Usually used before get_intersection().
	*/
	bool has_intersection(const Segment& s) const;
	/*
		 Get the intersection point of the two segments.
		 If they don't intersect, this function has undefined behaviour. 
		 TODO: This is just slow because makes us use get_intersection twice. Implement a better solution.
	*/
	Point get_intersection(const Segment& s) const;
	/*
	 Comparator function, returns a <= b when b's endpoint lies to the left of a's endpoint.
	*/
	bool operator<=(const Segment& s) const;
	
	/*
		Returns true iff this segment has larger slope than s, i.e if this segment goes above 's' after their intersection (if such exists).
	*/
	coord_type slope_above(const Segment& s) const;

};

#endif