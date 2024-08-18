
#include "derivatives.hpp"

#include <cstddef>   // std::size_t
#include <stdexcept> //std::invalid_argument

#include "hd/hd_stencil.hpp"

namespace hd {

void fd_dfdx_init(mdspan<double const, dextents<size_t, 1>> x,
                  mdspan<double, dextents<size_t, 1>> a0_f1,
                  mdspan<double, dextents<size_t, 1>> b0_f1,
                  mdspan<double, dextents<size_t, 1>> c0_f1)
{

    if (x.extent(0) != a0_f1.extent(0) || a0_f1.extent(0) != b0_f1.extent(0) ||
        b0_f1.extent(0) != c0_f1.extent(0)) {
        throw std::invalid_argument(
            "hd::fd_dfdx_init: Incompatible extents of grid and/or coefficients.");
    }

    size_t n = x.extent(0); // total index range: n = [0,n-1]

    std::vector<double> x0v(3);
    std::vector<double> x1v(1);
    std::vector<double> x2v{};

    {
        size_t i = 0;
        x0v[0] = x[i];
        x0v[1] = x[i + 1];
        x0v[2] = x[i + 2];
        x1v[0] = x[i];
        hd::stencil_t s(x[i], hd::stencil_lhs::f1, x0v, x1v, x2v);

        a0_f1[i] = s.wf0[0];
        b0_f1[i] = s.wf0[1];
        c0_f1[i] = s.wf0[2];
    }

    for (size_t i = 1; i < n - 1; ++i) {
        x0v[0] = x[i - 1];
        x0v[1] = x[i];
        x0v[2] = x[i + 1];
        x1v[0] = x[i];
        hd::stencil_t s(x[i], hd::stencil_lhs::f1, x0v, x1v, x2v);

        a0_f1[i] = s.wf0[0];
        b0_f1[i] = s.wf0[1];
        c0_f1[i] = s.wf0[2];
    }

    {
        size_t i = n - 1;
        x0v[0] = x[i - 2];
        x0v[1] = x[i - 1];
        x0v[2] = x[i];
        x1v[0] = x[i];
        hd::stencil_t s(x[i], hd::stencil_lhs::f1, x0v, x1v, x2v);

        a0_f1[i] = s.wf0[0];
        b0_f1[i] = s.wf0[1];
        c0_f1[i] = s.wf0[2];
    }
}

void fd_dfdx(mdspan<double const, dextents<size_t, 1>> a0_f1,
             mdspan<double const, dextents<size_t, 1>> b0_f1,
             mdspan<double const, dextents<size_t, 1>> c0_f1,
             mdspan<double const, dextents<size_t, 1>> u,
             mdspan<double, dextents<size_t, 1>> dudx)
{

    size_t n = a0_f1.extent(0); // total index range: n = [0,n-1]

    {
        size_t i = 0;
        dudx[i] = a0_f1[i] * u[i] + b0_f1[i] * u[i + 1] + c0_f1[i] * u[i + 2];
    }

    for (size_t i = 1; i < n - 1; ++i) {
        dudx[i] = a0_f1[i] * u[i - 1] + b0_f1[i] * u[i] + c0_f1[i] * u[i + 1];
    }

    {
        size_t i = n - 1;
        dudx[i] = a0_f1[i] * u[i - 2] + b0_f1[i] * u[i - 1] + c0_f1[i] * u[i];
    }
}

void fd_d2fdx2_init(mdspan<double const, dextents<size_t, 1>> x,
                    mdspan<double, dextents<size_t, 1>> a0_f2,
                    mdspan<double, dextents<size_t, 1>> b0_f2,
                    mdspan<double, dextents<size_t, 1>> c0_f2)
{

    if (x.extent(0) != a0_f2.extent(0) || a0_f2.extent(0) != b0_f2.extent(0) ||
        b0_f2.extent(0) != c0_f2.extent(0)) {
        throw std::invalid_argument(
            "hd::fd_dfdx_init: Incompatible extents of grid and/or coefficients.");
    }

    size_t n = x.extent(0); // total index range: n = [0,n-1]

    std::vector<double> x0v(3);
    std::vector<double> x1v{};
    std::vector<double> x2v(1);

    {
        size_t i = 0;
        x0v[0] = x[i];
        x0v[1] = x[i + 1];
        x0v[2] = x[i + 2];
        x2v[0] = x[i];
        hd::stencil_t s(x[i], hd::stencil_lhs::f2, x0v, x1v, x2v);

        a0_f2[i] = s.wf0[0];
        b0_f2[i] = s.wf0[1];
        c0_f2[i] = s.wf0[2];
    }

    for (size_t i = 1; i < n - 1; ++i) {
        x0v[0] = x[i - 1];
        x0v[1] = x[i];
        x0v[2] = x[i + 1];
        x2v[0] = x[i];
        hd::stencil_t s(x[i], hd::stencil_lhs::f2, x0v, x1v, x2v);

        a0_f2[i] = s.wf0[0];
        b0_f2[i] = s.wf0[1];
        c0_f2[i] = s.wf0[2];
    }

    {
        size_t i = n - 1;
        x0v[0] = x[i - 2];
        x0v[1] = x[i - 1];
        x0v[2] = x[i];
        x2v[0] = x[i];
        hd::stencil_t s(x[i], hd::stencil_lhs::f2, x0v, x1v, x2v);

        a0_f2[i] = s.wf0[0];
        b0_f2[i] = s.wf0[1];
        c0_f2[i] = s.wf0[2];
    }
}

void fd_d2fdx2(mdspan<double const, dextents<size_t, 1>> a0_f2,
               mdspan<double const, dextents<size_t, 1>> b0_f2,
               mdspan<double const, dextents<size_t, 1>> c0_f2,
               mdspan<double const, dextents<size_t, 1>> u,
               mdspan<double, dextents<size_t, 1>> d2udx2)
{

    size_t n = a0_f2.extent(0); // total index range: n = [0,n-1]

    {
        size_t i = 0;
        d2udx2[i] = a0_f2[i] * u[i] + b0_f2[i] * u[i + 1] + c0_f2[i] * u[i + 2];
    }

    for (size_t i = 1; i < n - 1; ++i) {
        d2udx2[i] = a0_f2[i] * u[i - 1] + b0_f2[i] * u[i] + c0_f2[i] * u[i + 1];
    }

    {
        size_t i = n - 1;
        d2udx2[i] = a0_f2[i] * u[i - 2] + b0_f2[i] * u[i - 1] + c0_f2[i] * u[i];
    }
}

} // namespace hd
