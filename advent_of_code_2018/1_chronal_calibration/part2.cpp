#include <iostream>
#include <string>
#include <unordered_set>
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
