#include "segment.h"

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
	coord_type t = delta2.x / delta1.x;
	return t >= 0 && t <= 1;
}

bool Segment::is_parallel(const Segment& s) const {
	Point delta1 = this->end - this->beg;
	Point delta2 = s.end - s.beg;
	return IS_ZERO(delta1.x * delta2.y - delta1.y * delta2.x);
}

bool Segment::has_intersection(const Segment& s) const {
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
	Point delta1 = s1.end - s1.beg;
	//TODO: This can be implemented better with vector operations
	coord_type m1 = delta1.y / delta1.x;
	Point delta2 = s2.end - s2.beg;
	coord_type m2 = delta2.y / delta2.x;
	coord_type c1 = s1.beg.y - m1 * s1.beg.x;
	coord_type c2 = s2.beg.y - m2 * s2.beg.x;
	// Calculate intersection point
	coord_type x_i = (c2 - c1) / (m1 - m2);
	coord_type y_i = m1 * x_i + c1;
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