#pragma once

#include <iostream>
#include <string>

template <typename T>
    requires(std::floating_point<T>)
struct vec2d {

    vec2d() = default;
    vec2d(T x_in, T y_in) : x(x_in), y(y_in) {}

    template <typename U>
        requires(std::floating_point<U>)
    vec2d(vec2d<U> const& v) : x(v.x), y(v.y)
    {
    }

    template <typename U> bool operator==(vec2d<U> const& rhs) const
    {
        auto abs_delta_x = std::abs(rhs.x - x);
        auto abs_delta_y = std::abs(rhs.y - y);
        auto constexpr delta_eps = 1.0e-7;
        if (abs_delta_x < delta_eps && abs_delta_y < delta_eps) return true;
        return false;
    }

    T x{};
    T y{};

    // comment out friend and implementation below to see lua table types directly
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, vec2d<U> const& v);
};

template <typename T>
    requires(std::floating_point<T>)
std::ostream& operator<<(std::ostream& os, vec2d<T> const& v)
{
    os << "(" << v.x << "," << v.y << ")";
    return os;
}

// defining consts
auto const e1_2d = vec2d<double>{1.0, 0.0};
auto const e2_2d = vec2d<double>{0.0, 1.0};


// unary minus
template <typename T>
    requires(std::floating_point<T>)
inline constexpr vec2d<T> operator-(vec2d<T> const& v)
{
    return vec2d<T>(-v.x, -v.y);
}

template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
vec2d<std::common_type_t<T, U>> operator+(vec2d<T> const& lhs, vec2d<U> const& rhs)
{
    return vec2d<std::common_type_t<T, U>>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
vec2d<std::common_type_t<T, U>> operator-(vec2d<T> const& lhs, vec2d<U> const& rhs)
{
    return vec2d<std::common_type_t<T, U>>(lhs.x - rhs.x, lhs.y - rhs.y);
}

// multiply a vector with a scalar (in both constellations)
template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline constexpr vec2d<std::common_type_t<T, U>> operator*(vec2d<T> const& v, U s)
{
    return vec2d<std::common_type_t<T, U>>(v.x * s, v.y * s);
}

template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline constexpr vec2d<std::common_type_t<T, U>> operator*(T s, vec2d<U> const& v)
{
    return vec2d<std::common_type_t<T, U>>(v.x * s, v.y * s);
}

////////////////////////////////////////////////////////////////////////////////
// check if we can distinguish two very similar types with same signature
////////////////////////////////////////////////////////////////////////////////

template <typename T>
    requires(std::floating_point<T>)
struct mvec2d_e {

    // ctors

    // (all grades = 0)
    mvec2d_e() = default;

    // assign all components
    mvec2d_e(T s, T ps) : c0(s), c1(ps) {}

    // floating point type conversion
    template <typename U>
        requires(std::floating_point<U>)
    mvec2d_e(mvec2d_e<U> const& v) : c0(v.c0), c1(v.c1)
    {
    }


    T c0{}; // scalar component
    T c1{}; // bivector component (2d pseudoscalar)

    // equality
    template <typename U>
        requires(std::floating_point<U>)
    bool operator==(mvec2d_e<U> const& rhs) const
    {
        // componentwise comparison
        // equality implies same magnitude and direction
        // comparison is not exact, but accepts epsilon deviations
        auto abs_delta_c0 = std::abs(rhs.c0 - c0);
        auto abs_delta_c1 = std::abs(rhs.c1 - c1);
        auto constexpr delta_eps = 1.0e-7;
        if (abs_delta_c0 < delta_eps && abs_delta_c1 < delta_eps) return true;
        return false;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, mvec2d_e<U> const& v);
};

// for printing via iostream
template <typename T>
    requires(std::floating_point<T>)
std::ostream& operator<<(std::ostream& os, mvec2d_e<T> const& v)
{
    os << "(" << v.c0 << "," << v.c1 << ")";
    return os;
}

////////////////////////////////////////////////////////////////////////////////
// mvec2d_e<T> core operations
////////////////////////////////////////////////////////////////////////////////

// unary minus
template <typename T>
    requires(std::floating_point<T>)
inline constexpr mvec2d_e<T> operator-(mvec2d_e<T> const& v)
{
    return mvec2d_e<T>(-v.c0, -v.c1);
}

// add multivectors
template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline constexpr mvec2d_e<std::common_type_t<T, U>> operator+(mvec2d_e<T> const& v1,
                                                              mvec2d_e<U> const& v2)
{
    return mvec2d_e<std::common_type_t<T, U>>(v1.c0 + v2.c0, v1.c1 + v2.c1);
}

// substract multivectors
template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline constexpr mvec2d_e<std::common_type_t<T, U>> operator-(mvec2d_e<T> const& v1,
                                                              mvec2d_e<U> const& v2)
{
    return mvec2d_e<std::common_type_t<T, U>>(v1.c0 - v2.c0, v1.c1 - v2.c1);
}


// multiply a multivector with a scalar
template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline constexpr mvec2d_e<std::common_type_t<T, U>> operator*(mvec2d_e<T> const& v, U s)
{
    return mvec2d_e<std::common_type_t<T, U>>(v.c0 * s, v.c1 * s);
}

template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline constexpr mvec2d_e<std::common_type_t<T, U>> operator*(T s, mvec2d_e<U> const& v)
{
    return mvec2d_e<std::common_type_t<T, U>>(v.c0 * s, v.c1 * s);
}

template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline constexpr mvec2d_e<std::common_type_t<T, U>> gpr(mvec2d_e<T> const& a,
                                                        mvec2d_e<U> const& b)
{
    using ctype = std::common_type_t<T, U>;
    return mvec2d_e<ctype>(a.c0 * b.c0 - a.c1 * b.c1, a.c0 * b.c1 + a.c1 * b.c0);
}

// define complex multiplication with operator*(a,b) as an alias for gpr(a,b)
template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline constexpr mvec2d_e<std::common_type_t<T, U>> operator*(mvec2d_e<T> const& a,
                                                              mvec2d_e<U> const& b)
{
    using ctype = std::common_type_t<T, U>;
    return gpr<ctype>(a, b);
}


template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline std::common_type_t<T, U> dot(vec2d<T> const& v1, vec2d<U> const& v2)
{
    // this implementation is only valid in an orthonormal basis
    return v1.x * v2.x + v1.y * v2.y;
}

template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline std::common_type_t<T, U> wdg(vec2d<T> const& v1, vec2d<U> const& v2)
{
    return std::common_type_t<T, U>(v1.x * v2.y - v1.y * v2.x);
}

template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline constexpr mvec2d_e<std::common_type_t<T, U>> gpr(vec2d<T> const& a,
                                                        vec2d<U> const& b)
{
    using ctype = std::common_type_t<T, U>;
    return mvec2d_e<ctype>(ctype(dot(a, b)), wdg(a, b));
}

// define geometric multiplication with operator*(a,b) as an alias for gpr(a,b)
template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline constexpr mvec2d_e<std::common_type_t<T, U>> operator*(vec2d<T> const& a,
                                                              vec2d<U> const& b)
{
    using ctype = std::common_type_t<T, U>;
    return gpr<ctype>(a, b);
}


template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline constexpr vec2d<std::common_type_t<T, U>> gpr(mvec2d_e<T> const& a,
                                                     vec2d<U> const& b)
{
    using ctype = std::common_type_t<T, U>;
    return vec2d<ctype>(a.c0 * b.x + a.c1 * b.y, a.c0 * b.y - a.c1 * b.x);
}

// define geometric multiplication with operator*(a,b) as an alias for gpr(a,b)
template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline constexpr vec2d<std::common_type_t<T, U>> operator*(mvec2d_e<T> const& a,
                                                           vec2d<U> const& b)
{
    using ctype = std::common_type_t<T, U>;
    return gpr<ctype>(a, b);
}

template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline constexpr vec2d<std::common_type_t<T, U>> gpr(vec2d<T> const& a,
                                                     mvec2d_e<U> const& b)
{
    using ctype = std::common_type_t<T, U>;
    return vec2d<ctype>(a.x * b.c0 - a.y * b.c1, a.x * b.c1 + a.y * b.c0);
}

// define geometric multiplication with operator*(a,b) as an alias for gpr(a,b)
template <typename T, typename U>
    requires(std::floating_point<T> && std::floating_point<U>)
inline constexpr vec2d<std::common_type_t<T, U>> operator*(vec2d<T> const& a,
                                                           mvec2d_e<U> const& b)
{
    using ctype = std::common_type_t<T, U>;
    return gpr<ctype>(a, b);
}
