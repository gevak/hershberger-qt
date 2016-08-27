#ifndef __SEGMENT_HEADER_FILE
#define __SEGMENT_HEADER_FILE

#include <limits>
#include <iostream>
#include <vector>

#include "util.h"

typedef double coord_type; // I'm skipping the possiblity to implement a rational number class and use it, but that would have been the correct thing to do


//TODO: Do I want to have operator= implementations?

//TODO: This is a hacky solution, do something better
bool IS_ZERO(coord_type val);

class Point;
class Segment;


/*
	Represents a point. 
	The y-coord can be infinity, for which we have INFINITE_VALUE defined.
*/
class Point {
public:
	static coord_type INFINITE_VALUE;
	coord_type x, y;
	/*
	 Constructor from x,y coords.
	*/
	Point(coord_type x=0, coord_type y=0);
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

	bool is_below(const Segment& s) const;

	coord_type square_dist(const Point& p) const;

};

std::ostream& operator<<(std::ostream& os, const Point& p);

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

	void set_endpoints(const Point & beg, const Point & end);

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
	bool operator<(const Segment& s) const;
	
	/*
		Returns true iff this segment has larger slope than s, i.e if this segment goes above 's' after their intersection (if such exists).
	*/
	coord_type slope_above(const Segment& s) const;

	bool is_infinite_height() const;

	bool is_vertical() const;

	Point get_point_at_x(coord_type x) const;

	bool crosses_x(coord_type x) const;

	bool is_above(const Point& p) const;

};

std::ostream& operator<<(std::ostream& os, const Segment& s);

std::ostream& operator<<(std::ostream& os, const std::vector<Segment>& s);

#endif