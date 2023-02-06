////////////////////////////////////////////////////////////////////////////////
// author: Daniel Hug, 2022
//
// intent: solve the linear advection-diffusion equation
//
// du(t,x)/dt + c * du(t,x)/dx = d * d2u(t,x)/dx2 [+ src(t,x)]
//
// - time integration via Runge-Kutta scheme of 4th-order
// - space discretized by a grid that need not be equidistant
//   with finite and/or compact finite differences used for spacial derivatives
//
////////////////////////////////////////////////////////////////////////////////

#include "fmt/format.h"
#include "fmt/ranges.h"
// #include "mdspan/mdspan.hpp"
#include <experimental/mdspan>

#include <cmath>   // std::sin
#include <cstddef> // std::size_t
#include <numbers> // std::numbers::pi
using std::numbers::pi;
#include <vector>

#include "derivatives.hpp"
#include "grid.hpp"
#include "output.hpp"
#include "rk4.hpp"

/*

ToDo:

- set up basic program functionality
- create output (vtk and/or qt-coordsys)
- switch to input of all constants or input parameters, e.g. via Lua or Json input files
- switch from constant dt to variable dt
- include measure for total error

*/

// make mdspan less verbose
using std::experimental::dextents;
using std::experimental::dynamic_extent;
using std::experimental::extents;
using std::experimental::layout_left;
using std::experimental::layout_right;
using std::experimental::mdspan;

int main(int argc, char* argv[])
{

    const std::size_t XPTS = 101;      // grid pts in x-direction
    const std::size_t TIMESTEPS = 800; // pts in t-direction (time steps)

    // grid coordinates t
    std::vector<double> t_mem = hd::get_grid(hd::grid_t::equidistant, hd::rng_t{0.0, 6.0}, TIMESTEPS);
    auto t = mdspan<double, extents<int, TIMESTEPS>>(t_mem.data());

    // grid coordinates x
    std::vector<double> x_mem = hd::get_grid(hd::grid_t::equidistant, hd::rng_t{0.0, 10.0}, XPTS);
    auto x = mdspan<double, extents<int, XPTS>>(x_mem.data());

    // memory for u (t_j, x_i)
    std::vector<double> u_mem(XPTS, 0.0);
    auto u = mdspan<double, extents<int, XPTS>>(u_mem.data());

    // memory for rhs = -c*dudx + d*d2udx2 at the four RK steps (space operator)
    std::vector<double> rhs_mem(XPTS, 0.0);
    auto rhs = mdspan<double, extents<int, XPTS>>(rhs_mem.data());

    // helper for time integration (idx 0: at t, idx: summation field)
    std::vector<double> uh_mem(2 * XPTS, 0.0);
    auto uh = mdspan<double, extents<int, 2, XPTS>>(uh_mem.data());

    // memory for dudx
    std::vector<double> dudx_mem(XPTS, 0.0);
    auto dudx = mdspan<double, extents<int, XPTS>>(dudx_mem.data());

    // memory for d2udx2
    std::vector<double> d2udx2_mem(XPTS, 0.0);
    auto d2udx2 = mdspan<double, extents<int, XPTS>>(d2udx2_mem.data());

    // coefficients for f  (x_i) in stencil for f'
    std::vector<double> a0_f1_mem(XPTS), b0_f1_mem(XPTS), c0_f1_mem(XPTS);
    auto a0_f1 = mdspan<double, extents<int, XPTS>>(a0_f1_mem.data());
    auto b0_f1 = mdspan<double, extents<int, XPTS>>(b0_f1_mem.data());
    auto c0_f1 = mdspan<double, extents<int, XPTS>>(c0_f1_mem.data());

    // coefficients for f' (x_i) in stencil for f'
    std::vector<double> a1_f1_mem(XPTS), b1_f1_mem(XPTS), c1_f1_mem(XPTS);
    auto a1_f1 = mdspan<double, extents<int, XPTS>>(a1_f1_mem.data());
    auto b1_f1 = mdspan<double, extents<int, XPTS>>(b1_f1_mem.data());
    auto c1_f1 = mdspan<double, extents<int, XPTS>>(c1_f1_mem.data());

    // coefficients for f  (x_i) in stencil for f''
    std::vector<double> a0_f2_mem(XPTS), b0_f2_mem(XPTS), c0_f2_mem(XPTS);
    auto a0_f2 = mdspan<double, extents<int, XPTS>>(a0_f2_mem.data());
    auto b0_f2 = mdspan<double, extents<int, XPTS>>(b0_f2_mem.data());
    auto c0_f2 = mdspan<double, extents<int, XPTS>>(c0_f2_mem.data());

    // coefficients for f''(x_i) in stencil for f''
    std::vector<double> a2_f2_mem(XPTS), b2_f2_mem(XPTS), c2_f2_mem(XPTS); // coefficients for f''(x_i)
    auto a2_f2 = mdspan<double, extents<int, XPTS>>(a2_f2_mem.data());
    auto b2_f2 = mdspan<double, extents<int, XPTS>>(b2_f2_mem.data());
    auto c2_f2 = mdspan<double, extents<int, XPTS>>(c2_f2_mem.data());

    // fmt::print("x: [ {:.4} ]\n\n", fmt::join(x_mem, ", "));

    // initialize derivative calculations
    hd::fd_dfdx_init(x, a0_f1, b0_f1, c0_f1);
    hd::fd_d2fdx2_init(x, a0_f2, b0_f2, c0_f2);

    // fmt::print("a0_f1 [ {:.4} ]\n\n", fmt::join(a0_f1_mem, ", "));
    // fmt::print("b0_f1 [ {:.4} ]\n\n", fmt::join(b0_f1_mem, ", "));
    // fmt::print("c0_f1 [ {:.4} ]\n\n", fmt::join(c0_f1_mem, ", "));

    // fmt::print("a0_f2 [ {:.4} ]\n\n", fmt::join(a0_f2_mem, ", "));
    // fmt::print("b0_f2 [ {:.4} ]\n\n", fmt::join(b0_f2_mem, ", "));
    // fmt::print("c0_f2 [ {:.4} ]\n\n", fmt::join(c0_f2_mem, ", "));

    // {
    //     // Test case for dudx:
    //     // f = -(x-5)^2 + 1;
    //     // f' = -2x + 10;
    //     // f'' = -2;
    //     for (std::size_t i = 0; i < x.extent(0); ++i)
    //         u(i) = -1. * (x(i) - 5) * (x(i) - 5) + 1;

    //     hd::fd_dfdx(a0_f1, b0_f1, c0_f1, u, dudx);
    //     hd::fd_d2fdx2(a0_f2, b0_f2, c0_f2, u, d2udx2);

    //     fmt::print("u [ {:.4} ]\n\n", fmt::join(u_mem, ", "));
    //     fmt::print("dudx [ {:.4} ]\n\n", fmt::join(dudx_mem, ", "));
    //     fmt::print("d2udx2 [ {:.4} ]\n\n", fmt::join(d2udx2_mem, ", "));
    // }

    // initial value for u(t0,x) = 0. already set by initialization

    // hd::output_t otype = hd::output_t::none;
    hd::output_t otype = hd::output_t::vtp;

    double ampl = 2.0; // amplitude of source term
    double c = 6.28;   // convection speed
    double d = 0.1;    // diffusion constant

    // main time loop
    for (int nt = 0; nt < TIMESTEPS - 1; ++nt)
    {
        double dt = t(nt + 1) - t(nt);

        hd::write_to_file(otype, nt, x_mem, u_mem);

        // Runge-Kutte time integration scheme
        for (int rk_step = 0; rk_step < 4; ++rk_step)
        {
            double trk = hd::get_time_rkstep(t(nt), dt, rk_step);

            // set boundary condition in source-term at u(0)
            u(0) = ampl * std::sin(4 * pi * trk);

            // get space operator (rhs: of du/dt = rhs)
            hd::fd_dfdx(a0_f1, b0_f1, c0_f1, u, dudx);
            hd::fd_d2fdx2(a0_f2, b0_f2, c0_f2, u, d2udx2);

            for (int i = 0; i < XPTS; ++i)
            {
                rhs(i) = -c * dudx(i) + d * d2udx2(i);
            }

            // do the time integration
            hd::rk4_step(u, uh, rhs, dt, rk_step);
        }
    }
}