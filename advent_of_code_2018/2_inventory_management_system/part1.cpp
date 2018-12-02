#include <unordered_map>
#include <range/v3/istream_range.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <iostream>
#include <string>

struct scan_result {
    bool has_two = false;
    bool has_three = false;
};

scan_result scan_box(std::string_view id) {
    std::unordered_map<char, int> hits;
    for (auto c : id) {
        auto [_, inserted] = hits.emplace(c, 1);
        if (!inserted) ++hits[c];
    }
    scan_result r;
    for (auto [k,v] : hits) {
        if (v == 2) r.has_two = true; 
        else if (v == 3) r.has_three = true;
    }
    return r;
}

int main() {
    using namespace ranges;
    
    struct count {
        int n_twos = 0;
        int n_threes = 0;
    };

    auto accumulate_count = [](count c, scan_result s) { 
                                return count{c.n_twos + s.has_two, c.n_threes + s.has_three}; 
                            };
    auto final_count = accumulate(istream_range<std::string>(std::cin) | view::transform(scan_box),
                            count{}, accumulate_count);
    std::cout << final_count.n_twos * final_count.n_threes << '\n';                    
}