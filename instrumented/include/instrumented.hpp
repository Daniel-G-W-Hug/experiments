#pragma once

#include <cstddef> // size_t

#include "fmt/format.h"
#include "fmt/ranges.h"        // support printing of (nested) containers & tuples
using namespace fmt::literals; // just to make the format literals visible

/*
define a class instrumented<T> that instruments every regular type T
and counts the operations performed on the type T.

The target is to be able to evaluate and compare algorithm complexity.

Idea taken from Stepanov A9 lectures on "Efficient programming with components"

*/

// hint: non-const static members are declaration only, and need to be defined
// separately!
struct instrumented_base
{
    enum
    {
        n,
        dflt_ctor,
        dtor,
        cp_ctor,
        cp_assign,
        mv_ctor,
        mv_assign,
        equality,
        comparison,
        conversion_from_T,
        conversion_to_T
    };
    static const size_t number_ops = 11;
    static double counts[number_ops];
    static const char* counter_names[number_ops];
    static void initialize(size_t);
};

template <typename T>
struct instrumented : instrumented_base
{

    T value;

  public:
    // (implicit) conversions to and from T

    // for retrieving the type when provided as template argument
    // since the language does not provide an alternative
    using value_type = T;

    // explicit instrumented(const T& val) : value(val) { ++counts[conversion]; }
    // explicit operator T() const { return value; }
    instrumented(const T& val) : value(val) { ++counts[conversion_from_T]; }
    operator T() const
    {
        ++counts[conversion_to_T];
        return value;
    }

    // implicit conversion between different template argumentes
    template <typename U>
    instrumented(const instrumented<U>& x) : value(x.value) {}

    // semiregular
    instrumented() { ++counts[dflt_ctor]; } // default ctor

    ~instrumented() { ++counts[dtor]; }
    // dtor
    instrumented(const instrumented& other) : value(other.value)
    { // cp ctor
        ++counts[cp_ctor];
    }

    instrumented& operator=(const instrumented& other)
    { // cp assign
        value = other.value;
        ++counts[cp_assign];
        return *this;
    }

    instrumented(instrumented&& other) noexcept
        : value(std::move(other.value))
    { // mv ctor
        ++counts[mv_ctor];
    }

    instrumented& operator=(instrumented&& other) noexcept
    { // mv assign
        value = std::move(other.value);
        ++counts[mv_assign];
        return *this;
    }

    // regular (added equality & inequality)
    // (HINT: friend functions are not part of the struct or class!)
    friend bool operator==(const instrumented& lhs, const instrumented& rhs)
    {
        ++counts[equality];
        return lhs.value == rhs.value;
    }

    friend bool operator!=(const instrumented& lhs, const instrumented& rhs)
    {
        return !(lhs == rhs);
    }

    // totally ordered (added comparison operations)
    friend bool operator<(const instrumented& lhs, const instrumented& rhs)
    {
        ++counts[comparison];
        return lhs.value < rhs.value;
    }

    friend bool operator>=(const instrumented& lhs, const instrumented& rhs)
    {
        return !(lhs < rhs);
    }

    friend bool operator>(const instrumented& lhs, const instrumented& rhs)
    {
        return (rhs < lhs);
    }

    friend bool operator<=(const instrumented& lhs, const instrumented& rhs)
    {
        return !(rhs < lhs);
    }
};

// ----------------------------------------------------------------------------
// printing support via fmt library
// ----------------------------------------------------------------------------

// formating for user defined types (instrumented)
template <typename T>
struct fmt::formatter<instrumented<T>>
{
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx);
    template <typename FormatContext>
    auto format(const instrumented<T>& x, FormatContext& ctx);
};

template <typename T>
template <typename ParseContext>
constexpr auto fmt::formatter<instrumented<T>>::parse(ParseContext& ctx)
{
    return ctx.begin();
}

template <typename T>
template <typename FormatContext>
auto fmt::formatter<instrumented<T>>::format(const instrumented<T>& x,
                                             FormatContext& ctx)
{
    return fmt::format_to(ctx.out(), "{}", x.value);
}

// Bsp. für Anwendung
// std::vector<instrumented<int>> vp1{1, 2};
// fmt::print(" vp1 = {}\n", fmt::join(vp1, ", "));