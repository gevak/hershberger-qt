#ifndef __HERSHBERGER_HEADER_FILE
#define __HERSHBERGER_HEADER_FILE

#include <vector>
#include <iostream>
#include <algorithm>

#include "segment.h"
#include "util.h"

/*
	Calculates lower envelope using simple divide and conquer algorithm in time O(n \alpha(n) log n).
	Returns the lower envelope as a series of segments sorted by x value, which is not the best for some uses.
*/
std::vector<Segment> lower_envelope_dc(std::vector<Segment> segments);

/*
	Calculates lower envelope using hershberger's algorithm in time O(n log n).
	Returns the lower envelope as a series of segments sorted by x value, which is not the best for some uses.
*/
std::vector<Segment> lower_envelope_hersh(std::vector<Segment> segments);

/*
	Merges two lower envelope series in linear time using 'merge' algorithm,
	to obtain the lower envelope of both of them.
*/
std::vector<Segment> merge_envelopes(std::vector<Segment>& env1, std::vector<Segment>& env2);

/*
	Utility method for pretty-printing.
*/
void print_envelope(std::vector<Segment>& env);

#endif