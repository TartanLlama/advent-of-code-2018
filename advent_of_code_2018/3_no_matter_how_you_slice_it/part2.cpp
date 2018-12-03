#include <ctre.hpp>
#include <ctll.hpp>
#include <range/v3/getlines.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/utility/tuple_algorithm.hpp>
#include <range/v3/view/indices.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/view/filter.hpp>
#include <string_view>
#include <iostream>
#include <map>
#include <vector>
#include "tuple_drop.hpp"

using namespace ranges;

struct rectangle {
	int id, left, top, width, height;
};

static inline constexpr auto pattern = ctll::basic_fixed_string{ "#([0-9]+) @ ([0-9]+),([0-9]+): ([0-9]+)x([0-9]+)" };

rectangle parse_rectangle(std::string_view s) {
	auto captures = tl::tuple_drop(ctre::re<pattern>().match(s));
	auto args = tuple_transform(captures, [](auto&& x) { return std::stoi(std::string{ x.to_view() }); });
	auto make_rectangle = [](auto... ts) { return rectangle{ ts... }; };
	return std::apply(make_rectangle, args);
}

int main() {
	auto rects = getlines(std::cin) | view::transform(parse_rectangle) | to_vector;

	std::vector<std::vector<short>> id_hits(1'000'000);
	std::vector<bool> ids_intersected(rects.size());
	for (auto&& r : rects) {
		for (auto i : view::closed_indices(r.left, r.width + r.left - 1)) {
			for (auto j : view::closed_indices(r.top, r.height + r.top - 1)) {
				id_hits[i * 1000 + j].push_back(r.id);
			}
		}
	}
	for (auto&& ids : id_hits | view::filter([](auto&& v) { return v.size() > 1; })) {
		for (auto id : ids) ids_intersected[id-1] = true;
	}
	std::cout << (1 + distance(begin(ids_intersected), 
		            	       find_if(ids_intersected, [](auto&& p) { return p == false; })));
}