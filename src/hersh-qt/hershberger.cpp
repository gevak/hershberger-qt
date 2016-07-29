#include "hershberger.h"
#include <iterator>

using std::vector;
using std::iterator;
using std::advance;

vector<Segment> merge_envelopes(vector<Segment>& env1, vector<Segment>& env2) {
	vector<Segment> res;
	auto bot = env1;
	auto top = env2;
	unsigned int ib = 0, it = 0;
	// We always maintain that bot is the current lower envelope
	Point p1 = bot[ib].beg;
	Point p2 = top[it].beg;
	if (p2 < p1) {
		auto temp_env = bot;
		bot = top;
		top = temp_env;
		auto temp_p = p1;
		p1 = p2;
		p2 = temp_p;
		auto temp_i = ib;
		ib = it;
		it = temp_i;
	}
	while (bot[ib].end.x != Point::INFINITE_VALUE || top[it].end.x != Point::INFINITE_VALUE) {

		// When we check if they intersect, we also make sure to check that bot goes above top,
		// which may seem trivial, but if we don't check we will always get infinite loops after intersection points because the cut-out new segment also intersects.
		if (bot[ib].has_intersection(top[it]) && bot[ib].slope_above(top[it])) {
			// bot and top switch, replace them and cut them
			Point p_i = bot[ib].get_intersection(top[it]);
			
		}
		else {
			// We need to advance the segment that ends first.
			// If it's the bottom one we need to insert it and cut the other one afterwards.
			
			// We also want to make sure we 're-stitch' any split segment where both ends survived.
			// This can be easily achieve by remembering the last segment that we inserted into 'ans', 
			// and if we're about to enter part of the same segment we stitch them together.
			
		}
	}
	return vector<Segment>();
}

vector<Segment> lower_envelope_dc(vector<Segment> segments) {

	// We could split the vector by simply changing the end pointer and beg pointer in O(1)
	// This solution does cause our memory consumption to reach O(nlogn) which is not really necessary, 
	// but good enough since this isn't the algorithm we're here to implement
	// TODO: Improve this memory consumption
	if (segments.size() == 1) {
		vector<Segment> ans;
		Segment s = segments[0];
		Point min_inf(-Point::INFINITE_VALUE, Point::INFINITE_VALUE); //TODO: does this work?
		Point plus_inf(Point::INFINITE_VALUE, Point::INFINITE_VALUE);
		ans.push_back(Segment(min_inf, Point(s.beg.x, Point::INFINITE_VALUE)));
		ans.push_back(s);
		ans.push_back(Segment(Point(s.end.x, Point::INFINITE_VALUE), plus_inf));
		return ans;
	}
	
	vector<Segment> first_elements(segments.begin(), 
		segments.begin() + (segments.size() / 2));

	vector<Segment> last_elements(segments.begin() + (segments.size() / 2) + 1,
		segments.end());

	vector<Segment> first_env = lower_envelope_dc(first_elements);

	vector<Segment> last_env = lower_envelope_dc(last_elements);

	return merge_envelopes(first_env, last_env);
}