#ifndef HD_GRID_H
#define HD_GRID_H

#include <cstddef> // std::size_t
#include <vector>

// define grid for calculation

namespace hd
{

enum class grid_t
{
    equidistant,
};

struct rng_t
{
    double min, max;
};

std::vector<double> get_grid(grid_t gtype, rng_t rng, size_t n);

} // namespace hd

#endif // HD_GRID_H