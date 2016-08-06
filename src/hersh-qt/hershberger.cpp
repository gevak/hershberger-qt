#include <iterator>

#include "hershberger.h"

using std::vector;
using std::iterator;
using std::advance;

vector<Segment> merge_envelopes(vector<Segment>& env1, vector<Segment>& env2) {
	vector<Segment> res;
	auto bot = env1;
	auto top = env2;
	unsigned int ib = 0, it = 0;
	// We always maintain that bot is the current lower envelope, and bottom segment starts left to top
	// TODO avoid 'restitch' by extending bottom as much as we can each time, but remember to handle
	// cases where both segments go to infinity or top drops suddenly from above to below bot, which can be done by implementing segment.is_above(point).
	// TODO Maybe just handle the envelope as a set of continous segments, including vertical ones? This will avoid many of the cases here.

	// TODO We probably don't need this, they both start at infinity, but is it bad that we don't know which is top and which is bot?
	/* Point p_bot = bot[ib].beg;
	Point p_top = top[it].beg;
	if (p_top.y < p_bot.y) {
		SWAP(top, bot); // Note that this is a pointer swap, so it should be O(1)
		SWAP(it, ib);
	} */

	//bool restitch = false;
	while (bot[ib].end.x != Point::INFINITE_VALUE || top[it].end.x != Point::INFINITE_VALUE) {
		// When we check if they intersect, we also make sure to check that bot goes above top,
		// which may seem trivial, but if we don't check we will always get infinite loops after intersection points because the cut-out new segment also intersects.
		if (bot[ib].has_intersection(top[it]) && bot[ib].slope_above(top[it])) {
			// bot and top switch, so we cut them at intersection point
			Point p_i = bot[ib].get_intersection(top[it]);
			// Insert newly cut bottom segment to resulting envelope (+restitch if we need to).
			res.push_back(Segment(bot[ib].beg, p_i));
			// Cut the segments from the intersection point, don't change list indices, and swap them
			top[it].beg = p_i;
			bot[ib].beg = p_i;
			SWAP(top, bot);
			SWAP(it, ib);
			//restitch = false;
		} 
		else {
			// We need to advance the segment that ends first.
			if (bot[ib].end.x < top[it].end.x) {
				// bottom ends first, we need to cut the top one, insert bot to envelope, and increase bot index.
				// We first check if the new bottom segment begins above top, because then we need to swap them.
				bool swap_order = false;
				if (!top[it].is_above(bot[ib + 1].beg)) {
					swap_order = true;
				}
				top[it].beg = top[it].get_point_at_x(bot[ib].end.x);
				res.push_back(bot[ib]);
				ib++;
				// If the next bottom segment is at infinity, top just became the bottom.
				// Otherwise, bottom is still below (it is continous).
				if (swap_order) {
					SWAP(top, bot);
					SWAP(ib, it);
				}
				// restitch = false;

			}
			else {
				// top ends first, so increase top index. Don't insert bot yet because it might continue to be the bottom segment.
				// If the new top segment starts below bot, we split bot and insert it, and swap them.
				it++;
				if (top[it].beg.is_below(bot[ib])) {
					res.push_back(Segment(bot[ib].beg, bot[ib].get_point_at_x(top[it].beg.x)));
					bot[ib] = Segment(bot[ib]);
					bot[ib].beg = bot[ib].get_point_at_x(top[it].beg.x);
					SWAP(top, bot);
					SWAP(ib, it);
				}
				else { // Top starts above bot, so we simply move on
					;
				}
				//restitch = true;

			}
			
		}
	}
	// Insert last infinite segment which we won't get from any of the envelopes
	coord_type last_x = res[res.size() - 1].end.x;
	Point plus_inf = Point(Point::INFINITE_VALUE, Point::INFINITE_VALUE);
	res.push_back(Segment(Point(last_x, Point::INFINITE_VALUE), plus_inf));
	return res;
}

vector<Segment> lower_envelope_dc(vector<Segment> segments) {

	// We could split the vector by simply changing the end pointer and beg pointer in O(1)
	// This solution does cause our memory consumption to reach O(nlogn) which is not really necessary, 
	// but good enough since this isn't the algorithm we're here to implement
	// TODO: Improve this memory consumption
	if (segments.size() <= 0) {
		vector<Segment> ans;
		Point min_inf(-Point::INFINITE_VALUE, Point::INFINITE_VALUE);
		Point plus_inf(Point::INFINITE_VALUE, Point::INFINITE_VALUE);
		ans.push_back(Segment(min_inf, plus_inf));
		return ans;
	}

	if (segments.size() == 1) {
		vector<Segment> ans;
		Segment s = segments[0];
		Point min_inf(-Point::INFINITE_VALUE, Point::INFINITE_VALUE);
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