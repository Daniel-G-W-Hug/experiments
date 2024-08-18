#ifndef HD_OUTPUT_H
#define HD_OUTPUT_H

#include <string>
#include <vector>

// create file-output for ode simulation values

#include "mdspan/mdspan.hpp"

// make mdspan less verbose
using namespace Kokkos;

namespace hd {

enum class output_t {
    none,
    print,
    vtp,
};

struct point_3d // for vtp file output
{
    double x, y, z;
};

void write_to_file(output_t const otype, size_t nt, std::vector<double> const& x,
                   std::vector<double> const& u);

} // namespace hd

#endif // HD_OUTPUT_H