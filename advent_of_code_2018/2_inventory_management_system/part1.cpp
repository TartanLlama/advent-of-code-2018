/*
Problem:
Input is strings delimited on newlines
For each string, check if there is at least one character repeated two times
Also check if there is at least one character repeated three times
Add together the number of strings with two-repeated characters,
  multiply by the number with three-repeated characters

 Approach:
 For each string, sort it and group the characters that are equal
 Check if there's a group which has two elements and/or one with three elements
 Accumulate the results of these checks as we go, and multiply at the end
*/

#include <unordered_map>
#include <range/v3/istream_range.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/view/group_by.hpp>
#include <iostream>
#include <string>

int main() {
    using namespace ranges;
    
	int pairs = 0;
	int triples = 0;

	for (auto&& s : istream_range<std::string>(std::cin)) {
		//sort carries out a sort on the range (aptly named, huh?)
		//  It is an action, which means it is carried out immediately, unlike a view.
		//group_by will split the range into subranges of characters which satisfy the predicate
		//  (in this case, the ones which are equal)
		auto groups = action::sort(s) | view::group_by(equal_to{});

		//This helper will tell us if there's a sub-group in our group which has the given size
		auto has_group_of_size = [] (auto&& rng, std::size_t n) {
			return find_if(rng, [n](auto&& g) { return distance(g) == n; }) != end(rng);
		};

		if (has_group_of_size(groups,2)) ++pairs;
		if (has_group_of_size(groups,3)) ++triples;
	}

    std::cout << pairs * triples << '\n';                    
}