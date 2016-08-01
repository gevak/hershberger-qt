#include "segment.h"
#include <cassert>
#include <algorithm>

coord_type Point::INFINITE_VALUE = std::numeric_limits<coord_type>::infinity();

//TODO: This is a hacky solution, do something better
bool IS_ZERO(coord_type val) {
	coord_type EPSILON = 0.00001;
	return val < EPSILON && val > -EPSILON;
}


/*
	Point class implementation.
*/

Point::Point(coord_type x=0, coord_type y=0) : x(x), y(y) {};

Point::Point(const Point& p) {
	this->x = p.x;
	this->y = p.y;
}

Point Point::operator-(const Point& p) const {
	return Point(this->x - p.x, this->y - p.y);
}

Point Point::operator+(const Point& p) const {
	return Point(this->x + p.x, this->y + p.y);
}

bool Point::operator<(const Point& p) const {
	return this->x < p.x || (this->x == p.x && this->y < p.y);
};

bool Point::operator==(const Point& p) const {
	return this->x == p.x && this->y == p.y;
};

/*
	Segment class implemetation.
*/

Segment::Segment(const Point& beg, const Point& end) : beg(beg), end(end) {};

Segment::Segment(const Segment& s) : beg(s.beg), end(s.end) {}; 

bool Segment::operator<=(const Segment& s) const {
	return this->end < s.end;
}

/*
	TODO: This is inaccurate. Implement a better solution.
*/
bool Segment::contains(const Point& p) const {
	Point delta1 = this->end - this->beg;
	Point delta2 = p - this->beg;
	if (!IS_ZERO(delta1.x * delta2.y - delta1.y * delta2.x)) {
		// Point not even on the infinite line
		return false;
	}
	;
	if (this->is_vertical()) {
		return p.y >= std::min(this->beg.y, this->end.y) && p.y <= std::max(this->beg.y, this->end.y);
	}
	coord_type t = delta2.x / delta1.x;
	return t >= 0 && t <= 1;
}

bool Segment::is_parallel(const Segment& s) const {
	Point delta1 = this->end - this->beg;
	Point delta2 = s.end - s.beg;
	return IS_ZERO(delta1.x * delta2.y - delta1.y * delta2.x);
}

bool Segment::has_intersection(const Segment& s) const {
	if (this->is_vertical() && s.is_vertical()) {
		return false;
	}
	if (this->is_parallel(s)) {
		// Segments are parallel, return false
		return false;
	}
	Point p = this->get_intersection(s);
	return this->contains(p) && s.contains(p);
}

Point Segment::get_intersection(const Segment& s2) const {
	// We assume that the segments are non-parallel
	Segment s1 = *this;
	if (s2.is_vertical()) {
		return s2.get_intersection(s1); // Since only one of them can be vertical, this can't cause an infinite loop
	}
	Point delta1 = s1.end - s1.beg;
	//TODO: This can be implemented better with vector operations
	// We know s2 is not vertical
	Point delta2 = s2.end - s2.beg;
	coord_type m2 = delta2.y / delta2.x;
	coord_type c2 = s2.beg.y - m2 * s2.beg.x;
	coord_type x_i;
	coord_type y_i;
	// Calculate intersection point
	if (s1.is_vertical()) {
		x_i = s1.beg.x;
		y_i = m2 * x_i + c2;
	}
	else {
		coord_type m1 = delta1.y / delta1.x;
		coord_type c1 = s1.beg.y - m1 * s1.beg.x;
		x_i = (c2 - c1) / (m1 - m2);
		y_i = m1 * x_i + c1;
	}
	
	return Point(x_i, y_i);
}

coord_type Segment::slope_above(const Segment& s2) const {
	Segment s1 = *this;
	Point delta1 = s1.end - s1.beg;
	Point delta2 = s2.end - s2.beg;
	if (delta1.x * delta2.x > 0) { // Multiplying by negative switches inequality sign
		return delta1.y * delta2.x >= delta2.y * delta1.x;
	}
	return delta1.y * delta2.x <= delta2.y * delta1.x;

}

bool Segment::is_infinite_height() const {
	if (this->beg.y == Point::INFINITE_VALUE) {
		assert(this->end.y == Point::INFINITE_VALUE);
		return true;
	}
	return false;
}

bool Segment::is_vertical() const
{
	return this->beg.x == this->end.x;
}

Point Segment::get_point_at_x(coord_type x) const
{
	assert(this->beg.x <= x && this->end.x >= x);
	return this->get_intersection(Segment(Point(x, -Point::INFINITE_VALUE), Point(x, Point::INFINITE_VALUE)));
}
