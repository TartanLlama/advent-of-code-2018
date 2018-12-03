#include <iostream>
#include <string>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/istream_range.hpp>

int main()
{
	using namespace ranges;
	std::cout << accumulate(istream_range<int>(std::cin), 0) << '\n';
}
