#include <range/v3/istream_range.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/cartesian_product.hpp>
#include <range/v3/view/zip.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/take.hpp>
#include <functional>
#include <iostream>

using namespace ranges;

int main() {
	auto hamming_distance = [](auto&& r1, auto&& r2) { 
		return accumulate(view::zip(r1, r2), 0, ranges::plus{},
			[](auto&& x) { return x.first != x.second; }); 
	};

	auto ns = ranges::istream_range<std::string>(std::cin) | to_vector;
	auto found = view::cartesian_product(ns, ns) 
		       | view::filter([&](auto&& p) { return hamming_distance(get<0>(p), get<1>(p)) == 1; });
	for (auto [s1,s2] : found | view::take(1)) {
		for (auto[c1, c2] : view::zip(s1, s2)) {
			if (c1 == c2) std::cout << c1;
		}
	}
}