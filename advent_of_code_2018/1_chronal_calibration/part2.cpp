#include <iostream>
#include <string>
#include <unordered_set>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/istream_range.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/view/partial_sum.hpp>
#include <range/v3/view/cycle.hpp>
#include "lift.hpp"

int main()
{
	using namespace ranges;

    std::unordered_set<long> hits;
    auto nums = istream_range<int>(std::cin) | to_vector;

	for (auto&& frequency : nums | view::cycle | view::partial_sum()) {
        if (auto[_, inserted] = hits.insert(frequency); !inserted) {
            std::cout << frequency << '\n';
            return 0;
        }
    }
}
