#include <ctre.hpp>
#include <ctll.hpp>
#include <range/v3/getlines.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/utility/tuple_algorithm.hpp>
#include <range/v3/view/indices.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <string_view>
#include <iostream>
#include <map>
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
	enum class state : char { unclaimed, claimed, hot };
	std::map<std::pair<int, int>, state> hot_map;
	auto rects = getlines(std::cin) | view::transform(parse_rectangle);
	for (auto&& r : rects) {
		for (auto i : view::closed_indices(r.left, r.width+r.left-1)) {
			for (auto j : view::closed_indices(r.top, r.height+r.top-1)) {
				auto index = std::make_pair(i, j);
				auto[_, inserted] = hot_map.emplace(index, state::claimed);
				if (!inserted) hot_map[index] = state::hot;
			}
		}
	}

	std::cout << accumulate(hot_map, 0, plus{}, [](auto&& p) { return p.second == state::hot;  });
}