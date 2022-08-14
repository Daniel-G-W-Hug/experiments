#include <iostream>
using std::cout;

#include <algorithm> // std::copy
#include <list>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include "hd/hd_keypress.hpp"

#include "fmt/format.h"
#include "fmt/ranges.h" // support printing of (nested) containers & tuples

using namespace fmt::literals; // just to make the format literals visible

std::string h{}; // history string  (print later to view history)

// history version (stores output in global string)
template <typename T>
struct noisy_h
{
    T t;
    noisy_h() { h += "default-ctor "; }
    ~noisy_h() { h += "dtor "; }
    noisy_h(const noisy_h &rhs) : t(rhs.t) { h += "copy-ctor "; }
    noisy_h(noisy_h &&rhs) : t(std::move(rhs.t)) { h += "move-ctor "; }
    auto operator=(const noisy_h &rhs)
    {
        h += "copy-assign ";
        t = rhs.t;
        return *this;
    }
    auto operator=(noisy_h &&rhs)
    {
        h += "move-assign ";
        t = std::move(rhs.t);
        return *this;
    }
};

// print version (prints to std::out)
template <typename T>
struct noisy_p
{
    T t;
    noisy_p() { fmt::print("default-ctor\n"); }
    ~noisy_p() { fmt::print("dtor\n"); }
    noisy_p(const noisy_p &rhs) : t(rhs.t) { fmt::print("copy-ctor\n"); }
    noisy_p(noisy_p &&rhs) : t(std::move(rhs.t)) { fmt::print("move-ctor\n"); }
    auto operator=(const noisy_p &rhs)
    {
        fmt::print("copy-assign\n");
        t = rhs.t;
        return *this;
    }
    auto operator=(noisy_p &&rhs)
    {
        fmt::print("move-assign\n");
        t = std::move(rhs.t);
        return *this;
    }
};

// // test various containers and nested containers
// std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
// std::vector<std::vector<int>> vvi = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

// std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};
// std::list<std::list<int>> lli = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

// std::vector<std::list<int>> vli = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
// std::list<std::vector<int>> lvi = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

// std::vector<int> vlong;

// std::vector<std::string> vs = {"Nils", "Marlena", "Pie", "Daniel"};

// std::set si = {1, 2, 3, 4, 5, 6, 7, 8, 9};

// std::tuple<int, double, std::string> tids = {1, 1.0, "1.0"};

// std::map<int, std::string> mis = {{1, "eins"}, {2, "zwei"}, {3, "drei"}};

// std::vector<std::tuple<int, double, std::string>> vtids = {
//     {1, 1.0, "1.0"}, {2, 2.0, "2.0"}, {3, 3.0, "3.0"}};

std::vector<int> v1{1, 2, 3};
std::vector<int> v2{4, 5, 6};

// template <typename T> struct pt2d { T x, y; };

// // formating for user defined types
// template <typename T> struct fmt::formatter<pt2d<T>> {
//   template <typename ParseContext> constexpr auto parse(ParseContext& ctx);
//   template <typename FormatContext>
//   auto format(const pt2d<T>& pt, FormatContext& ctx);
// };

// template <typename T>
// template <typename ParseContext>
// constexpr auto fmt::formatter<pt2d<T>>::parse(ParseContext& ctx) {
//   return ctx.begin();
// }

// template <typename T>
// template <typename FormatContext>
// auto fmt::formatter<pt2d<T>>::format(const pt2d<T>& pt, FormatContext& ctx) {
//   // return fmt::format_to(ctx.out(), "{{{0}, {1}}}", pt.x, pt.y);
//   return fmt::format_to(ctx.out(), "({0}, {1})", pt.x, pt.y);
// }

// std::vector<pt2d<double>> vp1{{1.0, 1.0}, {1.5, 2.0}};
// std::vector<pt2d<double>> vp2{{2.0, 4.0}, {2.5, 6.0}};

struct pt2d
{
    double x{0.0}, y{0.0};
    // pt2d() = default;
    // pt2d(double x_in, double y_in) :
    //     x(x_in), y(y_in) {}
    // ~pt2d() = default;
    // pt2d(const pt2d& rhs) = default;
    // pt2d(pt2d&& rhs) = default;
    // pt2d& operator=(const pt2d& rhs) = default;
    // pt2d& operator=(pt2d&& rhs) = default;
};

// noisy version of pt2d
struct pt2d_n
{
    double x{0.0}, y{0.0};
    pt2d_n() { fmt::print("default-ctor\n"); }
    pt2d_n(double x_in, double y_in) : x(x_in), y(y_in)
    {
        fmt::print("Two arg ctor\n");
    }
    ~pt2d_n() { fmt::print("dtor\n"); }

    pt2d_n(const pt2d_n &rhs) : x(rhs.x), y(rhs.y) { fmt::print("copy-ctor\n"); }
    pt2d_n(pt2d_n &&rhs) : x(std::move(rhs.x)), y(std::move(rhs.y))
    {
        fmt::print("move-ctor\n");
    }
    auto operator=(const pt2d_n &rhs)
    {
        fmt::print("copy-assign\n");
        x = rhs.x;
        y = rhs.y;
        return *this;
    }
    auto operator=(pt2d_n &&rhs)
    {
        fmt::print("move-assign\n");
        x = std::move(rhs.x);
        y = std::move(rhs.y);
        return *this;
    }
};

// formating for user defined types (pt2d)
template <>
struct fmt::formatter<pt2d>
{
    template <typename ParseContext>
    constexpr auto parse(ParseContext &ctx);
    template <typename FormatContext>
    auto format(pt2d const &pt, FormatContext &ctx) const;
};

template <typename ParseContext>
constexpr auto fmt::formatter<pt2d>::parse(ParseContext &ctx)
{
    return ctx.begin();
}

template <typename FormatContext>
auto fmt::formatter<pt2d>::format(pt2d const &pt, FormatContext &ctx) const
{
    // return fmt::format_to(ctx.out(), "{{{0}, {1}}}", pt.x, pt.y);
    return fmt::format_to(ctx.out(), "({}, {})", pt.x, pt.y);
}

// formating for user defined types (pt2d_n)
template <>
struct fmt::formatter<pt2d_n>
{
    template <typename ParseContext>
    constexpr auto parse(ParseContext &ctx);
    template <typename FormatContext>
    auto format(pt2d_n const &pt, FormatContext &ctx) const;
};

template <typename ParseContext>
constexpr auto fmt::formatter<pt2d_n>::parse(ParseContext &ctx)
{
    return ctx.begin();
}

template <typename FormatContext>
auto fmt::formatter<pt2d_n>::format(pt2d_n const &pt, FormatContext &ctx) const
{
    // return fmt::format_to(ctx.out(), "{{{0}, {1}}}", pt.x, pt.y);
    return fmt::format_to(ctx.out(), "({}, {})", pt.x, pt.y);
}

std::vector<pt2d> vp1{{1.0, 1.0}, {1.5, 2.0}};
std::vector<pt2d> vp2{{2.0, 4.0}, {2.5, 6.0}};
// std::vector<pt2d> vp1{pt2d{1.0, 1.0}, pt2d{1.5, 2.0}};
// std::vector<pt2d> vp2{pt2d{2.0, 4.0}, pt2d{2.5, 6.0}};

int main()
{

    //   fmt::print(" x = {:.2f}\n", fmt::join(x, ", "));
    fmt::print(" v1 = {}\n", fmt::join(v1, ", "));
    fmt::print(" v2 = {}\n", fmt::join(v2, ", "));

    std::copy(v2.begin(), v2.end(), std::back_inserter(v1));
    fmt::print(" v1 = {}\n", fmt::join(v1, ", "));

    pt2d p{1.0, 2.0};
    fmt::print(" p = {}\n", p);

    fmt::print(" vp1 = {}\n", fmt::join(vp1, ", "));
    fmt::print(" vp2 = {}\n", fmt::join(vp2, ", "));

    std::copy(vp2.begin(), vp2.end(), std::back_inserter(vp1));
    fmt::print(" vp1 = {}\n", fmt::join(vp1, ", "));

    fmt::print("\nTesting the noisy version pt2d_n:\n\n");
    {
        pt2d_n p1;
        fmt::print(" p1 = {}\n", p1);

        std::vector<pt2d_n> vn;

        double xmin = -1.0;
        double xmax = 1.0;
        double dx = 0.2;

        for (double x = xmin; x <= xmax; x += dx)
        {

            // pt2d_n p(x, std::exp(x));
            // vn.push_back(p);

            // vn.push_back(pt2d_n(x, std::exp(x)));

            vn.emplace_back(pt2d_n{x, std::exp(x)});
        }
        // fmt::print(" vp3 = {}\n", fmt::join(vp3, ", "));
    }
    // using pt2d_n = noisy_p<pt2d>;
    // std::vector<pt2d_n> vp3;

    // double xmin = -1.0;
    // double xmax = 1.0;
    // double dx = 0.2;

    // for (double x = xmin; x <= xmax; x += dx) {

    //   pt2d_n p(x, std::exp(x));
    //   vp3.push_back(p);

    // vp3.push_back(pt2d(x, std::exp(x)));

    // vp3.emplace_back(pt2d_n{x, std::exp(x)});
    // }
    // fmt::print(" vp3 = {}\n", fmt::join(vp3, ", "));

    // cout << "\nHello world with fmt library!\n\n";
    // fmt::print("Don't {}\n", "panic");
    // fmt::print("The answer is {}.\n", 42);
    // fmt::print("I'd rather be {1} than {0}.\n", "right", "happy");
    // fmt::print("Hello, {name}! The answer is {number}. Goodbye, {name}.\n",
    //            "name"_a = "World", "number"_a = 42);

    // std::string s = fmt::format("{0}{1}{0}\n", "abra", "cad");
    // fmt::print(s);
    // std::string message = "{0}{1}{0}\n"_format("abra", "cad");
    // fmt::print(message);

    // fmt::print("vi = {}\n", vi);
    // fmt::print("vvi = {}\n", vvi);
    // fmt::print("li = {}\n", vi);
    // fmt::print("lli = {}\n", vvi);
    // fmt::print("vli = {}\n", vli);
    // fmt::print("lvi = {}\n", lvi);

    // for (int i = 1; i < 300; ++i)
    //   vlong.push_back(i);
    // fmt::print("vlong = {}\n", vlong);

    // fmt::print("vs = {}\n", vs);

    // fmt::print("si = {}\n", si);
    // fmt::print("tids = {}\n", tids);
    // fmt::print("mis = {}\n", mis);
    // fmt::print("vtids = {}\n", vtids);

    //   fmt::print(" x = {:.2f}\n", fmt::join(x, ", "));

    for (int i = 0; i < 100; ++i)
    {
        fmt::print("fname{:0>4}\n", i);
    }

    hd::cmdl_wait_for_enter();

    return 0;
}
