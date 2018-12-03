/*
Problem:
Input file consists of integers delimited by newlines, e.g.
+13
-1
+4

The count starts at 0. Each integer modifies the count. Find the first count which is repeated.
Note: the input may need to be looped over before the count is repeated

Approach: 
Maintain an unordered_set of counts we have already seen.
Each time we add a number to the count, insert the new count into the set.
If we try to insert the count but it was already there, we've found the answer.
*/

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

	//hits will store which counts have been seen
	//unordered_set will let us quickly find if a count has been seen before
    std::unordered_set<long> hits;
	
	//The pipe(|) operator here acts like a Unix pipe; it takes the left hand side
	//  and passes it as input to the right. This lets us form a clear pipeline of
	//  data transformations.
	//to_vector will flush all the ints from the range into a vector
	//We do this because we may need to cycle over the input, but once the data
	//  is read from the istream_range, we can't get it back
    auto nums = istream_range<int>(std::cin) | to_vector;

	//cycle will view the vector as a ring, so once the last element is produced,
	//  the view will loop back round
	//partial_sum will maintain our count for us
	//Note that cycle and partial_sum are both views; they produce output on demand
	for (auto&& frequency : nums | view::cycle | view::partial_sum()) {
		//A couple of C++17 features help here:
		// 1. Structured bindings lets us name the elements of the pair which insert returns.
		//      The underscore is a handy "I don't care about this" identifier.
		// 2. The if initializer scopes the names to the if statement
        if (auto[_, inserted] = hits.insert(frequency); !inserted) {
            std::cout << frequency << '\n';
            return 0;
        }
    }
}
