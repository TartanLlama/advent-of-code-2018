#include <range/v3/istream_range.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/zip.hpp>
#include <range/v3/distance.hpp>
#include <range/v3/view/remove_if.hpp>
#include <functional>
#include <iostream>
#include "tl-range/k_combinations.hpp"

using namespace ranges;

template <class Rng1, class Rng2>
int hamming_distance(Rng1&& r1, Rng2&&r2) {
    return accumulate(view::zip(r1,r2), 0, ranges::plus{},
                     [](auto&& x) { return x.first != x.second; });
}

auto second = [](auto&& p) { return p.second; };

int main() {
    auto ns = ranges::istream_range<std::string>(std::cin) | to_vector;
    for (auto i = begin(ns); i != end(ns); ++i) {
        for (auto j = next(i); j != end(ns); ++j) {
            if (hamming_distance(*i, *j) == 1) {
              for (auto idx = 0; idx < i->size(); ++idx){
                  if((*i)[idx] == (*j)[idx]) std::cout << (*i)[idx];
              }
            }
        }
    }
}