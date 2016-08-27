#include <iterator>
#include <list>
#include <assert.h>
#include "hershberger.h"

using std::vector;
using std::iterator;
using std::list;
using std::copy_if;


vector<Segment> concat_envelopes(vector<Segment>& env1, vector<Segment>& env2) {
	vector<Segment> ret = env1;
	ret[ret.size() - 1] = Segment(env1[env1.size() - 1].beg, env2[0].end); // Connect them with infinite segment
	ret.insert(ret.end(), env2.begin() + 1, env2.end()); // Skip the first (infinite) segment of env2
	return ret;
}

vector<Segment> merge_multiple_envelopes(vector<vector<Segment>>& envs) {
	if (envs.empty()) {
		vector<Segment> ans;
		Point min_inf(-Point::INFINITE_VALUE, Point::INFINITE_VALUE);
		Point plus_inf(Point::INFINITE_VALUE, Point::INFINITE_VALUE);
		ans.push_back(Segment(min_inf, plus_inf));
		return ans;
	}
	if (envs.size() == 1) {
		return envs[0];
;	}
	vector<vector<Segment>> first_elements(envs.begin(),
		envs.begin() + (envs.size() / 2));

	vector<vector<Segment>> last_elements(envs.begin() + (envs.size() / 2),
		envs.end());

	return merge_envelopes(merge_multiple_envelopes(first_elements), merge_multiple_envelopes(last_elements));
}

vector<Segment> merge_envelopes(vector<Segment>& env1, vector<Segment>& env2) {
	//std::cout << "env1: \n " << env1 << std::endl;
	//std::cout << "env2: \n " << env2 << std::endl;
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
			}
			
		}
	}
	// Insert last infinite segment which we won't get from any of the envelopes
	coord_type last_x = res[res.size() - 1].end.x;
	Point plus_inf = Point(Point::INFINITE_VALUE, Point::INFINITE_VALUE);
	res.push_back(Segment(Point(last_x, Point::INFINITE_VALUE), plus_inf));
	//std::cout << "res: \n " << res << std::endl;
	//std::cout << " ---------------------------------------  " << std::endl;
	return res;
}

vector<Segment> lower_envelope_dc(vector<Segment>& segments) {

	// We could split the vector by simply changing the end pointer and beg pointer in O(1)
	// This solution does cause our memory consumption to reach O(nlogn) which is not really necessary, 
	// but good enough since this isn't the algorithm we're here to implement
	// TODO: Improve this memory consumption
	//std::cout << "segments: \n" << segments << std::endl;
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

	vector<Segment> last_elements(segments.begin() + (segments.size() / 2),
		segments.end());

	vector<Segment> first_env = lower_envelope_dc(first_elements);

	vector<Segment> last_env = lower_envelope_dc(last_elements);

	return merge_envelopes(first_env, last_env);
}

/*
* Gets the segments sorted by beg.x, the level number and the array of levels.
* Calculates the envelope of the lines intersecting the median x, and concats to the currently build envelope at the given level,
* and continues recursively for child sets.
*/
void hersh_level(vector<Segment>& segments, vector<vector<Segment>>& levels, unsigned int level) {
	if (segments.empty()) {
		return;
	}
	coord_type median = segments[segments.size() / 2].beg.x;
	vector<Segment> vertically_cut, left, right;
	copy_if(segments.begin(), segments.end(),
		std::back_inserter(vertically_cut),
		[&](const Segment& seg) { return seg.crosses_x(median); });

	copy_if(segments.begin(), segments.end(),
		std::back_inserter(left),
		[&](const Segment& seg) { return !seg.crosses_x(median) && seg.beg.x <= median; });

	copy_if(segments.begin(), segments.end(),
		std::back_inserter(right),
		[&](const Segment& seg) { return !seg.crosses_x(median) && seg.beg.x > median; });

	// Add the lower envelope of the vertically intersected segments to the level
	vertically_cut = lower_envelope_dc(vertically_cut);
	if (levels.size() <= level) { // Initialize the level
		assert(levels.size() == level);
		levels.push_back(vertically_cut); //TODO: fix slow copies like this
	}
	else {
		levels[level] = concat_envelopes(levels[level], vertically_cut); // Concat to the end, since we're going from left to right
	}
	hersh_level(left, levels, level + 1);
	hersh_level(right, levels, level + 1);
}

vector<Segment> lower_envelope_hersh(vector<Segment> segments) {
	std::sort(segments.begin(), segments.end()); // Sort segments by beg.x to find medians easily
	vector<vector<Segment>> levels;
	// Recursively calculate all the levels
	hersh_level(segments, levels, 0);
	// Recursively merge the envelopes in a tree structure -
	// they are envelopes of disjoint sets of segments, so merging each level will have low complexity and there are loglog(n) levels
	return merge_multiple_envelopes(levels);
}