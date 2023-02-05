#ifndef HD_OUTPUT_H
#define HD_OUTPUT_H

#include <string>
#include <vector>

// create file-output for ode simulation values

// #include "mdspan/mdspan.hpp"
#include <experimental/mdspan>

// make mdspan less verbose
using std::experimental::dextents;
using std::experimental::dynamic_extent;
using std::experimental::extents;
using std::experimental::layout_left;
using std::experimental::layout_right;
using std::experimental::mdspan;

namespace hd
{

enum class output_t
{
    none,
    print,
    vtp,
};

struct point_3d // for vtp file output
{
    double x, y, z;
};

void write_to_file(output_t const otype,
                   std::string const& fname,
                   int nt,
                   std::vector<double> const& x,
                   std::vector<double> const& u);

} // namespace hd

#endif // HD_OUTPUT_H