#ifndef HD_RK4_H
#define HD_RK4_H
////////////////////////////////////////////////////////////////////////////////
// time integration with Runge-Kutta 4-step method of 4th order
//
// du/dt = rhs(t,u(t)), u(t0)=u0
//
// with:
//  k1 = rhs(t_i       , u_i)             for Pred. 1: Euler forward to t+0.5*dt
//  k2 = rhs(t_i + dt/2, u_i + dt/2*k1)   for Corr. 1: Euler backward to t+0.5*dt
//  k3 = rhs(t_i + dt/2, u_i + dt/2*k2)   for Pred. 2: Midpoint rule to t+dt
//  k4 = rhs(t_i + dt  , u_i + dt*k3)     for Corr. 2: Simpson rule to t+dt
//
// u_i+1 = u_i + dt/6*(k1 + 2*k2 + 2*k3 + k4)
//
////////////////////////////////////////////////////////////////////////////////

#include "mdspan/mdspan.hpp"

// make mdspan less verbose
using Kokkos::dextents;
using Kokkos::dynamic_extent;
using Kokkos::extents;
using Kokkos::layout_left;
using Kokkos::layout_right;
using Kokkos::mdspan;

namespace hd
{

double get_time_rkstep(double ti, double dt, int rk);

void rk4_step(mdspan<double, dextents<int, 1>> u,
              mdspan<double, dextents<int, 2>> uh,
              mdspan<double const, dextents<int, 1>> rhs,
              double const dt,
              int const rk_step);

} // namespace hd

#endif // HD_RK4_H