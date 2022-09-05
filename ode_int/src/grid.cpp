#include "grid.hpp"

namespace hd
{

std::vector<double> get_grid(grid_t gtype, rng_t rng, size_t n)
{
    std::vector<double> grid(n);

    switch (gtype)
    {
    case (grid_t::equidistant):
    {
        double delta = (rng.max - rng.min) / (n - 1);
        for (int i = 0; i < n; ++i)
        {
            grid[i] = rng.min + i * delta;
        }
    }
    } // switch gtype

    return grid;
}

} // namespace hd