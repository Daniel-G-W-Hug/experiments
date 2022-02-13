#include <algorithm> // fill
#include <cstddef>   // size_t

#include "instrumented.hpp"

// define static members
double instrumented_base::counts[number_ops];
const char* instrumented_base::counter_names[number_ops] = {
    "n",
    "dflt_ctor",
    "dtor",
    "cp_ctor",
    "cp_assign",
    "mv_ctor",
    "mv_assign",
    "equality",
    "comparison",
    "conversion_from_T",
    "conversion_to_T"};

void instrumented_base::initialize(size_t m)
{
    std::fill(counts, counts + number_ops, 0.0);
    counts[n] = double(m);
}
