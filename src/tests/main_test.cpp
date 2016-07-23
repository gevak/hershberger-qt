#define BOOST_TEST_MODULE HershbergerTests
#include <boost/test/unit_test.hpp>
#include "hershberger.h"

int add(int i, int j) { return i + j; }

bool points_equal(Point p1, Point p2) {
	float EPSILON = 0.00001;
	return abs(p1.x - p2.x) < EPSILON && abs(p1.y - p2.y) < EPSILON;
}

BOOST_AUTO_TEST_CASE(test_segment_contains_point) 
{
	Segment s = Segment(Point(-1, -1), Point(1, 1));
	BOOST_CHECK(s.contains(Point(0, 0)));
	BOOST_CHECK(!s.contains(Point(0.5, 0)));

	// seven ways to detect and report the same error:
	BOOST_CHECK(add(2, 2) == 4);        // #1 continues on error

	BOOST_REQUIRE(add(2, 2) == 4);      // #2 throws on error

	if (add(2, 2) != 4)
		BOOST_ERROR("Ouch...");            // #3 continues on error

	if (add(2, 2) != 4)
		BOOST_FAIL("Ouch...");             // #4 throws on error

	if (add(2, 2) != 4) throw "Ouch..."; // #5 throws on error

	BOOST_CHECK_MESSAGE(add(2, 2) == 4,  // #6 continues on error
		"add(..) result: " << add(2, 2));

	BOOST_CHECK_EQUAL(add(2, 2), 4);	  // #7 continues on error
}

BOOST_AUTO_TEST_CASE(test_segment_intersection) 
{
	Segment s1(Point(0, -1), Point(2, 1));
	Segment s2(Point(0, 1), Point(2, -1));
	BOOST_REQUIRE(s1.has_intersection(s2));
	BOOST_CHECK(points_equal(s1.get_intersection(s2), Point(1, 0)));

	Segment s3(Point(-3, 1), Point(-2, -1));
	BOOST_CHECK(!s1.has_intersection(s3));

	// Parallel segments
	Segment s4(Point(0, -0.5), Point(2, 1.5));
	BOOST_CHECK(!s1.has_intersection(s4));
	BOOST_CHECK(s2.has_intersection(s4));

	Segment s5(Point(0, -0.5), Point(2, 3));
	BOOST_REQUIRE(s1.has_intersection(s5));

}