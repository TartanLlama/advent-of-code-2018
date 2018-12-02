#include <iostream>
#include <string>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/istream_range.hpp>

#include "lift.hpp"

int main()
{
	using namespace ranges;
	std::cout << accumulate(istream_range<std::string>(std::cin)
	                        | view::transform(LIFT(std::stoi)),
	                        0) << '\n';
}
