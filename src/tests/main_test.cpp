#define BOOST_TEST_MODULE HershbergerTests
#include <boost/test/unit_test.hpp>
#include <vector>

#include "hershberger.h"

using std::vector;

int add(int i, int j) { return i + j; }

bool points_equal(Point p1, Point p2) {
	coord_type EPSILON = 0.00001;
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
	BOOST_REQUIRE(!s1.has_intersection(s5));

}

BOOST_AUTO_TEST_CASE(test_vertical_segments) 
{
	Segment s1(Point(0, -1), Point(0, 2));
	Segment s2(Point(-2, 1), Point(2, 1));
	BOOST_REQUIRE(s1.has_intersection(s2));
	BOOST_CHECK(points_equal(s1.get_intersection(s2), Point(0, 1)));

	Segment s21(Point(-2, 0), Point(4, 3));
	BOOST_REQUIRE(s1.has_intersection(s21));
	BOOST_CHECK(points_equal(s1.get_intersection(s21), Point(0, 1)));

	Segment s3(Point(-3, 1), Point(-2, -1));
	BOOST_CHECK(!s1.has_intersection(s3));

	// Parallel segments
	Segment s4(Point(1, -0.5), Point(1, 1.5));
	BOOST_CHECK(!s1.has_intersection(s4));

	Segment s41(Point(0, 3), Point(0, 5));
	BOOST_CHECK(!s1.has_intersection(s41));

	Segment s5(Point(-1, -2), Point(1, 16));
	BOOST_REQUIRE(!s1.has_intersection(s5));
}


/*
BOOST_AUTO_TEST_CASE(test_merge)
{
vector<Segment> segs1;
segs1.push_back(Segment(Point(-Point::INFINITE_VALUE, Point::INFINITE_VALUE), Point(0, Point::INFINITE_VALUE)));
segs1.push_back(Segment(Point(0, 1), Point(2, 1)));
segs1.push_back(Segment(Point(2, Point::INFINITE_VALUE), Point(Point::INFINITE_VALUE, Point::INFINITE_VALUE)));
vector<Segment> segs2;
segs2.push_back(Segment(Point(-Point::INFINITE_VALUE, Point::INFINITE_VALUE), Point(3, Point::INFINITE_VALUE)));
segs2.push_back(Segment(Point(3, 1), Point(4, 1)));
segs2.push_back(Segment(Point(4, Point::INFINITE_VALUE), Point(Point::INFINITE_VALUE, Point::INFINITE_VALUE)));
vector<Segment> ans = merge_envelopes(segs1, segs2);
BOOST_REQUIRE_EQUAL(ans.size(), 5);
BOOST_REQUIRE(ans[0].is_infinite_height());
BOOST_REQUIRE(points_equal(ans[1].beg, Point(0, 1)));
BOOST_REQUIRE(points_equal(ans[1].end, Point(2, 1)));
BOOST_REQUIRE(ans[2].is_infinite_height());
BOOST_REQUIRE(points_equal(ans[3].beg, Point(3, 1)));
BOOST_REQUIRE(points_equal(ans[3].end, Point(4, 1)));
BOOST_REQUIRE(ans[4].is_infinite_height());

} */


BOOST_AUTO_TEST_CASE(test_envelope)
{
	vector<Segment> segs;
	segs.push_back(Segment(Point(-1, 1), Point(0, 1)));
	segs.push_back(Segment(Point(1, 1), Point(2, 1)));
	segs.push_back(Segment(Point(3, 1), Point(4, -2)));
	vector<Segment> ans = lower_envelope_dc(segs);
	BOOST_REQUIRE_EQUAL(ans.size(), 7);
	BOOST_REQUIRE(ans[0].is_infinite_height());
	BOOST_REQUIRE(points_equal(ans[1].beg, Point(-1, 1)));
	BOOST_REQUIRE(points_equal(ans[3].beg, Point(1, 1)));
	BOOST_REQUIRE(points_equal(ans[5].beg, Point(3, 1)));
	BOOST_REQUIRE(points_equal(ans[5].end, Point(4, -2)));
	segs.clear();
	segs.push_back(Segment(Point(-2, -1), Point(2, 3)));
	segs.push_back(Segment(Point(-1.5, 0), Point(2.5, 0)));
	segs.push_back(Segment(Point(0, 1), Point(3, -2)));
	ans = lower_envelope_dc(segs);
	BOOST_REQUIRE_EQUAL(ans.size(), 5);
	BOOST_REQUIRE(ans[0].is_infinite_height());
	BOOST_REQUIRE(points_equal(ans[1].beg, Point(-2, -1)));
	BOOST_REQUIRE(points_equal(ans[2].beg, Point(-1, 0)));
	BOOST_REQUIRE(points_equal(ans[3].beg, Point(1, 0)));
	BOOST_REQUIRE(points_equal(ans[3].end, Point(3, -2)));
} 