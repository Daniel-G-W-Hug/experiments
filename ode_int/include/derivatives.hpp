#ifndef HD_DERIVATIVES_H
#define HD_DERIVATIVES_H

#include "mdspan/mdspan.hpp"

// make mdspan less verbose
using std::experimental::dextents;
using std::experimental::dynamic_extent;
using std::experimental::extents;
using std::experimental::layout_left;
using std::experimental::layout_right;
using std::experimental::mdspan;

// finite difference space discritization of linear advection-diffusion-equation
//
// computation for all terms of rhs incl. du/dx, d2u/dx2 and source term

namespace hd
{

////////////////////////////////////////////////////////////////////////////
// FD-O2        i = 0:           i = [1,n-2]:     i = n-1:
//
//     f1:      x                     x                     x
//              |                     |                     |
//     f0:      . -- . -- .      . -- . -- .      . -- . -- .
//
//    idx:     i   i+1  i+2     i-1   i   i+1    i-2  i-1   i
////////////////////////////////////////////////////////////////////////////

// initialize coefficients (must be called once before use of fd_dfdx)
void fd_dfdx_init(mdspan<double const, dextents<int, 1>> x,
                  mdspan<double, dextents<int, 1>> a0_f1,
                  mdspan<double, dextents<int, 1>> b0_f1,
                  mdspan<double, dextents<int, 1>> c0_f1);

// returns dudx for u(x_i) (call fd_dfdx_init beforehand!)
void fd_dfdx(mdspan<double const, dextents<int, 1>> a0_f1,
             mdspan<double const, dextents<int, 1>> b0_f1,
             mdspan<double const, dextents<int, 1>> c0_f1,
             mdspan<double const, dextents<int, 1>> u,
             mdspan<double, dextents<int, 1>> dudx);

////////////////////////////////////////////////////////////////////////////
// FD-O2        i = 0:           i = [1,n-2]:     i = n-1:
//
//     f2:      x                     x                     x
//              |                     |                     |
//     f0:      . -- . -- .      . -- . -- .      . -- . -- .
//
//    idx:     i   i+1  i+2     i-1   i   i+1    i-2  i-1   i
////////////////////////////////////////////////////////////////////////////

// initialize coefficients (must be called once before use of fd_dfdx)
void fd_d2fdx2_init(mdspan<double const, dextents<int, 1>> x,
                    mdspan<double, dextents<int, 1>> a0_f2,
                    mdspan<double, dextents<int, 1>> b0_f2,
                    mdspan<double, dextents<int, 1>> c0_f2);

// returns d2udx2 for u(x_i) (call fd_dfdx_init beforehand!)
void fd_d2fdx2(mdspan<double const, dextents<int, 1>> a0_f2,
               mdspan<double const, dextents<int, 1>> b0_f2,
               mdspan<double const, dextents<int, 1>> c0_f2,
               mdspan<double const, dextents<int, 1>> u,
               mdspan<double, dextents<int, 1>> d2udx2);

} // namespace hd

#endif // HD_DERIVATIVES_H