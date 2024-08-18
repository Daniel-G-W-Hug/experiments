#include "fmt/format.h"
#include "fmt/ranges.h" // support printing of (nested) containers & tuples

#include "tinysplinecxx.h"
#include <vector>

#include "hd/hd_keypress.hpp"


// using namespace fmt::literals; // just to make the format literals visible
//
// struct pt2d
// {
//     double x{0.0}, y{0.0};
//     // pt2d() = default;
//     // pt2d(double x_in, double y_in) :
//     //     x(x_in), y(y_in) {}
//     // ~pt2d() = default;
//     // pt2d(const pt2d& rhs) = default;
//     // pt2d(pt2d&& rhs) = default;
//     // pt2d& operator=(const pt2d& rhs) = default;
//     // pt2d& operator=(pt2d&& rhs) = default;
// };

// // formating for user defined types (pt2d)
// template <>
// struct fmt::formatter<pt2d>
// {
//     template <typename ParseContext>
//     constexpr auto parse(ParseContext &ctx);
//     template <typename FormatContext>
//     auto format(pt2d const &pt, FormatContext &ctx) const;
// };

// template <typename ParseContext>
// constexpr auto fmt::formatter<pt2d>::parse(ParseContext &ctx)
// {
//     return ctx.begin();
// }

// template <typename FormatContext>
// auto fmt::formatter<pt2d>::format(pt2d const &pt, FormatContext &ctx) const
// {
//     // return fmt::format_to(ctx.out(), "{{{0}, {1}}}", pt.x, pt.y);
//     return fmt::format_to(ctx.out(), "({}, {})", pt.x, pt.y);
// }


// std::vector<pt2d> vp1{{1.0, 1.0}, {1.5, 2.0}};
// std::vector<pt2d> vp2{{2.0, 4.0}, {2.5, 6.0}};
// // std::vector<pt2d> vp1{pt2d{1.0, 1.0}, pt2d{1.5, 2.0}};
// // std::vector<pt2d> vp2{pt2d{2.0, 4.0}, pt2d{2.5, 6.0}};

int main()
{

    // setting up a two-dimensional cubic spline with 4 control points
    // BSline(#Ctrl-pts, dimension, degree)
    constexpr int num_ctrl_pts = 4; // no. of control points
    constexpr int ndim = 2;         // dimension of control points
    constexpr int degree = 3;       // degree curve

    tinyspline::BSpline spline = tinyspline::BSpline(num_ctrl_pts, ndim, degree);
    std::vector<tinyspline::real> ctrl_pts = spline.controlPoints();
    ctrl_pts[0] = 0;
    ctrl_pts[1] = 0; // P0
    ctrl_pts[2] = 2;
    ctrl_pts[3] = 3; // P1
    ctrl_pts[4] = 7;
    ctrl_pts[5] = 4; // P2
    ctrl_pts[6] = 6;
    ctrl_pts[7] = 1; // P3
    spline.setControlPoints(ctrl_pts);

    // sample line in npts different points
    constexpr int npts = 11;
    std::vector<tinyspline::real> pts = spline.sample(npts);

    for (size_t i = 0; i < pts.size() / ndim - 1; ++i) {
        tinyspline::real px0 = pts[i * ndim];
        tinyspline::real py0 = pts[i * ndim + 1];
        tinyspline::real px1 = pts[(i + 1) * ndim];
        tinyspline::real py1 = pts[(i + 1) * ndim + 1];

        // draw line from p0 to p1 => line(p0,p1)
        fmt::print("i={:2}: p0x={:.2f}, p0y={:.2f}, p1x={:.2f}, p1y={:.2f}\n", i, px0,
                   py0, px1, py1);
    }

    //   fmt::print(" x = {:.2f}\n", fmt::join(x, ", "));

    // for (int i = 0; i < 100; ++i)
    // {
    //     fmt::print("fname{:0>4}\n", i);
    // }

    hd::cmdl_wait_for_enter();

    return 0;
}
