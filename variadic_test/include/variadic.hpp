#pragma once

#include "fmt/format.h"
#include <initializer_list>
#include <string>

// HINT: templates MUST be defined in header files, not in cpp files!
// (otherwise there will be linker errors: symbol not found!)

template <typename... Ts>
void variadic_print(std::string const& initial, const Ts&... args);

template <typename... Ts>
void variadic_print(std::string const& initial, Ts const&... args)
{
    fmt::println("variadic_print called with {} parameters.", sizeof...(args));

    fmt::println("{}: ", initial);

    size_t cnt{1};
    for (auto p : std::initializer_list<std::string>{args...}) {
        fmt::println("arg: {}, value: {}", cnt, p);
        ++cnt;
    }
    fmt::println("\n");
}