/*
Problem: Read newline-delimited strings from stdin and add them together
Approach: Not much to do but read 'em and add 'em
*/

#include <iostream>
#include <string>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/istream_range.hpp>

int main()
{
	using namespace ranges;
	//istream_range<int> will iterate over ints from the stream you give it, delimited on whitespace
	//It reads and produces these ints on-demand; not in one batch when the range is constructed
	//accumulate sums together all the ints produced from this range
	std::cout << accumulate(istream_range<int>(std::cin), 0) << '\n';
}
