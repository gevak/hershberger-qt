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
	// We always maintain that bot is the current lower envelope, and bottom segment starts left to top
	// TODO avoid 'restitch' by extending bottom as much as we can each time, but remember to handle
	// cases where both segments go to infinity or top drops suddenly from above to below bot, which can be done by implementing segment.is_above(point).
	// TODO Maybe just handle the envelope as a set of continous segments, including vertical ones? This will avoid many of the cases here.
	Point p_bot = bot[ib].beg;
	Point p_top = top[it].beg;
	if (p_top.y < p_bot.y) {
		SWAP(top, bot); // Note that this is a pointer swap, so it should be O(1)
		SWAP(it, ib);
	}
	// We also want to make sure we 're-stitch' any split segment where both ends survived.
	// This can be easily achieve by remembering if the last segment that we inserted was split and continued on the lower envelope, 
	// indicated by 'restitch=true', and if we're about to enter part of the same segment we stitch them together.
	bool restitch = false;
	while (bot[ib].end.x != Point::INFINITE_VALUE || top[it].end.x != Point::INFINITE_VALUE) {
		// When we check if they intersect, we also make sure to check that bot goes above top,
		// which may seem trivial, but if we don't check we will always get infinite loops after intersection points because the cut-out new segment also intersects.
		if (bot[ib].has_intersection(top[it]) && bot[ib].slope_above(top[it])) {
			// bot and top switch, so we swap them and cut them
			Point p_i = bot[ib].get_intersection(top[it]);
			SWAP(top, bot);
			SWAP(it, ib);
			// Insert newly cut segment to resulting envelope (+restitch if we need to).
			// TODO code
			if (restitch) {

			}
			// Cut the segments from the intersection point, don't change list indices
			top[it].beg = p_i;
			bot[ib].beg = p_i;
			restitch = false;
		} 
		else {
			// We need to advance the segment that ends first.
			if (bot[ib].end.x < top[it].end.x) {
				// bottom ends first, we need to insert it (+restitch?), and cut the top one, and increase bot index.
				
				ib++;
				// If the next bottom segment is infinite, top just became the bottom.
				// Otherwise, bottom is still below (it is continous).
				if (bot[ib].is_infinite_height()) {
					SWAP(top, bot);
					SWAP(ib, it);
				}
				restitch = false;

			}
			else {
				// top ends first, we need to split bot, insert it to env (+restitch?), and increase top index.
				// Since we split it in the middle we set 'restitch' to true.
				
				it++;
				restitch = true;

			}
			
			
		}
	}
	return res;
}

vector<Segment> lower_envelope_dc(vector<Segment> segments) {

	// We could split the vector by simply changing the end pointer and beg pointer in O(1)
	// This solution does cause our memory consumption to reach O(nlogn) which is not really necessary, 
	// but good enough since this isn't the algorithm we're here to implement
	// TODO: Improve this memory consumption
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