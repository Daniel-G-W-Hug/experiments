#ifndef HD_USE_INHERITANCE_HPP
#define HD_USE_INHERITANCE_HPP

#include <string>

#include "fmt/format.h"
#include "fmt/ranges.h"

namespace HD_INHERITANCE
{

void demo();

struct noisy_animal_with_id
{
    virtual std::string make_noise() const = 0;
    virtual int id() const = 0;

    virtual ~noisy_animal_with_id() {} // empty virtual base class destructor required
};

struct Cat : public noisy_animal_with_id
{

    Cat() = default;
    Cat(const std::string& name) :
        my_name{name} {}

    std::string make_noise() const override
    {
        return fmt::format("Cat says meow.");
    }

    int id() const override
    {
        return 1;
    }

    float extra() const { return 1.0f; }

    int cat_int = 1;
    double cat_double = 1.0;
    std::string my_name{"No name"};
};

struct Dog : public noisy_animal_with_id
{
    Dog() = default;
    Dog(const std::string& name) :
        my_name{name} {}

    std::string make_noise() const override
    {
        return fmt::format("Dog says wow.");
    }

    int id() const override
    {
        return 2;
    }

    int dog_int = 2;

    std::string my_name{"No name"};
};

} // namespace HD_INHERITANCE

#endif // HD_USE_INHERITANCE_HPP