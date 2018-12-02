#include <iostream>
#include <string>
#include <unordered_set>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/istream_range.hpp>
#include <range/v3/to_container.hpp>
#include "lift.hpp"

int main()
{
	using namespace ranges;
    long frequency = 0;
    std::unordered_set<long> hits;

    auto nums = istream_range<std::string>(std::cin)
              | view::transform(LIFT(std::stoi))
              | to_vector;

    while (true) {
	    for (auto&& i : nums) {
            frequency += i;
            auto [_, inserted] = hits.insert(frequency);
            if (!inserted) {
                std::cout << frequency << '\n';
                return 0;
            }
        }
    }
	
}
