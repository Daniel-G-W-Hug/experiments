#pragma once

#include <cstddef> // size_t
#include <iostream>
#include <type_traits> // common_type_t

template <class T> struct Number {
    T n;
};

template <class T, class U>
constexpr Number<std::common_type_t<T, U>> operator+(const Number<T>& lhs,
                                                     const Number<U>& rhs)
{
    return {lhs.n + rhs.n};
}

void describe(const char* expr, const Number<unsigned short>& x)
{
    std::cout << expr << "  is  Number<unsigned short>{" << x.n << "}\n";
}

void describe(const char* expr, const Number<unsigned int>& x)
{
    std::cout << expr << "  is  Number<unsigned int>{" << x.n << "}\n";
}

void describe(const char* expr, const Number<unsigned long>& x)
{
    std::cout << expr << "  is  Number<unsigned long>{" << x.n << "}\n";
}

void describe(const char* expr, const Number<unsigned long long>& x)
{
    std::cout << expr << "  is  Number<unsigned long long>{" << x.n << "}\n";
}

// size_t is just a type alias for an unsigned type, thus it would be a redefinition
// void describe(const char* expr, const Number<size_t>& x)
// {
//     std::cout << expr << "  is  Number<size_t>{" << x.n << "}\n";
// }

void describe(const char* expr, const Number<short>& x)
{
    std::cout << expr << "  is  Number<short>{" << x.n << "}\n";
}

void describe(const char* expr, const Number<int>& x)
{
    std::cout << expr << "  is  Number<int>{" << x.n << "}\n";
}

void describe(const char* expr, const Number<long>& x)
{
    std::cout << expr << "  is  Number<long>{" << x.n << "}\n";
}

void describe(const char* expr, const Number<long long>& x)
{
    std::cout << expr << "  is  Number<long long>{" << x.n << "}\n";
}

void describe(const char* expr, const Number<float>& x)
{
    std::cout << expr << "  is  Number<float>{" << x.n << "}\n";
}

void describe(const char* expr, const Number<double>& x)
{
    std::cout << expr << "  is  Number<double>{" << x.n << "}\n";
}

void describe(const char* expr, const Number<long double>& x)
{
    std::cout << expr << "  is  Number<long double>{" << x.n << "}\n";
}