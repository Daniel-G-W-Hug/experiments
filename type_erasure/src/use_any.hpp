#ifndef HD_USE_ANY_HPP
#define HD_USE_ANY_HPP

#include <string>

#include "fmt/format.h"
#include "fmt/ranges.h"

namespace HD_ANY
{

void demo();

struct Cat
{

    Cat() = default;
    Cat(const std::string& name) :
        my_name{name} {}

    std::string make_noise() const
    {
        return fmt::format("Cat says meow.");
    }

    int id() const
    {
        return 1;
    }

    float extra() const { return 1.0f; }

    int cat_int = 1;
    double cat_double = 1.0;
    std::string my_name{"No name"};
};

struct Dog
{
    Dog() = default;
    Dog(const std::string& name) :
        my_name{name} {}

    std::string make_noise() const
    {
        return fmt::format("Dog says wow.");
    }

    int id() const
    {
        return 2;
    }

    int dog_int = 2;

    std::string my_name{"No name"};
};

} // namespace HD_ANY

#endif // HD_USE_ANY_HPP