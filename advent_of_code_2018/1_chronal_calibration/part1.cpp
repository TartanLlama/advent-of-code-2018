#include <iostream>
#include <string>
#include <range/v3/all.hpp>

#define FWD(...) std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

#define LIFT(X) [](auto &&... args) \
    noexcept(noexcept(X(FWD(args)...)))  \
    -> decltype(X(FWD(args)...)) \
{  \
    return X(FWD(args)...); \
}

int main()
{
	using namespace ranges;
	std::cout << accumulate(istream_range<std::string>(std::cin)
	                        | view::transform(LIFT(std::stoi)),
	                        0);
}
