#include <algorithm> // sort
#include <iostream>
#include <vector>

#include "fmt/format.h"
#include "fmt/ranges.h"        // support printing of (nested) containers & tuples
using namespace fmt::literals; // just to make the format literals visible

#include "instrumented.hpp"

int main()
{

    std::vector<int> vec1{1, 0, 3, 1, -1, 3, 4, 7, 12, 3, 6, -3};
    fmt::print("\nvec1       : {}\n", vec1);
    std::sort(vec1.begin(), vec1.end());
    fmt::print("vec1 sorted: {}\n\n", vec1);

    {

        std::vector<instrumented<int>> vec1_i{1, 0, 3, 1, -1, 3,
                                              4, 7, 12, 3, 6, -3};

        // fmt::print("\nvec1_i       : {}\n", fmt::join(vec1_i, ", "));
        // std::sort(vec1_i.begin(), vec1_i.end());
        // fmt::print("\nvec1_i sorted: {}\n\n", fmt::join(vec1_i, ", "));
    }

    fmt::print("Default ctor: {}\n",
               instrumented<int>::counts[instrumented_base::dflt_ctor]);
    fmt::print("Default dtor: {}\n",
               instrumented<int>::counts[instrumented_base::dtor]);
    fmt::print("Default cp_ctor: {}\n",
               instrumented<int>::counts[instrumented_base::cp_ctor]);
    fmt::print("Default cp_assign: {}\n",
               instrumented<int>::counts[instrumented_base::cp_assign]);
    fmt::print("Default mv_ctor: {}\n",
               instrumented<int>::counts[instrumented_base::mv_ctor]);
    fmt::print("Default mv_assign: {}\n",
               instrumented<int>::counts[instrumented_base::mv_assign]);
    fmt::print("Default equality: {}\n",
               instrumented<int>::counts[instrumented_base::equality]);
    fmt::print("Default comparison: {}\n",
               instrumented<int>::counts[instrumented_base::comparison]);
    fmt::print("Default conversion from T: {}\n",
               instrumented<int>::counts[instrumented_base::conversion_from_T]);
    fmt::print("Default conversion to T: {}\n",
               instrumented<int>::counts[instrumented_base::conversion_to_T]);

    do
    {
        std::cout << '\n'
                  << "Press ENTER to continue...";
    } while (std::cin.get() != '\n');

    return 0;
}