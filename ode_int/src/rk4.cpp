#include "rk4.hpp"

#include <stdexcept> //std::invalid_argument

namespace hd
{

double get_time_rkstep(double ti, double dt, int rk)
{

    switch (rk)
    {
        case 0:
            return ti;
        case 1:
            [[fallthrough]];
        case 2:
            return ti + dt / 2.;
        case 3:
            return ti + dt;
        default:
            std::invalid_argument("hd::get_time_rkstep: rk out of range (0 <= rk < 4).");
            return 0.0; // just to silence compiler warnings
            break;
    } // switch (rk)
}

void rk4_step(mdspan<double, dextents<int, 1>> u,
              mdspan<double, dextents<int, 2>> uh,
              mdspan<double const, dextents<int, 1>> rhs,
              double const dt,
              int const rk_step)
{

    // currently u[0] is fixed by boundary condition of source term

    double rk1 = 1. / 6. * dt;
    double rk2 = 1. / 3. * dt;
    double rk3 = 1. / 2. * dt;
    double rk4 = dt;

    int n = u.extent(0);

    switch (rk_step)
    {
        case 1: // predictor 1: Euler forward to t + 0.5*dt
            for (int i = 1; i < n; ++i)
            {
                uh[0, i] = u[i];
            }
            for (int i = 1; i < n; ++i)
            {
                u[i] = uh[0, i] + rk3 * rhs[i];
                uh[1, i] = rk1 * rhs[i];
            }
            break;

        case 2: // corrector 1: Euler backward to t + 0.5*dt
            for (int i = 1; i < n; ++i)
            {
                u[i] = uh[0, i] + rk3 * rhs[i];
                uh[1, i] += rk2 * rhs[i];
            }
            break;

        case 3: // predictor 2: mitpoint rule to t + dt
            for (int i = 1; i < n; ++i)
            {
                u[i] = uh[0, i] + rk4 * rhs[i];
                uh[1, i] += rk2 * rhs[i];
            }
            break;

        case 4: // corrector 2: Simpson rule to t + dt
            for (int i = 1; i < n; ++i)
            {
                u[i] = uh[0, i] + uh[1, i] + rk1 * rhs[i];
            }
            break;
    }
}

} // namespace hd
