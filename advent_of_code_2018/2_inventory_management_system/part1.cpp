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
		auto groups = action::sort(s) | view::group_by(equal_to{});
		auto has_group_of_size = [] (auto&& rng, std::size_t n) {
			return find_if(rng, [n](auto&& g) { return distance(g) == n; }) != end(rng);
		};
		if (has_group_of_size(groups,2)) ++pairs;
		if (has_group_of_size(groups,3)) ++triples;

	}

    std::cout << pairs * triples << '\n';                    
}