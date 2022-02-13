// use branch "single-header" from mdspan github
//
// To try using subscript operator comment in macro below
// the header will by default also check for the feature macro, and enable it
// defining the macro to 0 will overwrite the automatic setting
// x86-64 clang (experimental auto NSDMI) supports the operator, but you need
// to explicitly comment in below macro
// #define MDSPAN_USE_BRACKET_OPERATOR 1

// To force enable operator() comment in the macro below
// You can enable both at the same time.
// #define MDSPAN_USE_PAREN_OPERATOR 1

#include "mdspan/mdspan.hpp"

#include <cstddef> // std::size_t

#include "fmt/format.h"
#include "fmt/ranges.h"

// make mdspan less verbose
using std::experimental::dynamic_extent;
using std::experimental::extents;
using std::experimental::layout_left;
using std::experimental::layout_right;
using std::experimental::mdspan;

void func(mdspan<int, extents<dynamic_extent, dynamic_extent>> s)
{

    // change last element
    s(s.extent(0) - 1, s.extent(1) - 1) = 22;
    // s[s.extent(0) - 1, s.extent(1) - 1] = 22;

    for (std::size_t i = 0; i < s.extent(0); ++i)
        for (std::size_t j = 0; j < s.extent(1); ++j)
            fmt::print("s({},{}) == {}\n", i, j, s(i, j));
    // fmt::print("s({},{}) == {}\n", i, j, s[i, j]);
}

int main()
{
    std::array d{0, 5, 1, 3, 8, 4, 2, 7, 6};
    std::array d2{12, 13, 14};

    double buffer[3 * 4] = {1.0, 2.0, 3.0, 4.0, 6.0, 8.0, 10.0, 12.0, 24.0, 48.0, 72.0, 96.0};
    auto fd = mdspan<double, extents<3, 4>>(buffer);

    fmt::print("fd = {}\n\n", buffer);

    fmt::print("d2 = {}\n\n", d2);

    mdspan m{d.data(), 3, 3}; // correct, size of view corresponds to data source
    // mdspan m{d.data(), 2, 2};  // also ok, but only mapping part of data to mdspan
    // mdspan m{d.data(), 3, 4}; // error (source too small; uninitiallized memory used)!

    for (std::size_t i = 0; i < m.extent(0); ++i)
        for (std::size_t j = 0; j < m.extent(1); ++j)
            fmt::print("m({},{}) == {}\n", i, j, m(i, j));
    // fmt::print("m({},{}) == {}\n", i, j, m[i, j]);

    fmt::print("\n");

    func(m);

    fmt::print("\n");

    for (std::size_t i = 0; i < m.extent(0); ++i)
        for (std::size_t j = 0; j < m.extent(1); ++j)
            fmt::print("m({},{}) == {}\n", i, j, m(i, j));
    // fmt::print("m({},{}) == {}\n", i, j, m[i, j]);

    fmt::print("d2 = {}\n\n", d2);
}
