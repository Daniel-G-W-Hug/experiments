#include "use_any.hpp"

#include <any>
#include <vector>

void HD_ANY::demo()
{

    using namespace HD_ANY;

    Cat c1;
    Cat c2{"Pussy"};

    Dog d1{"Knut"};

    fmt::print("\n\nUsing std::any...\n\n");
    fmt::print("cat c1.my_name: {}\n", c1.my_name);
    fmt::print("cat c2.my_name: {}\n", c2.my_name);
    fmt::print("dog d1.my_name: {}\n", d1.my_name);
    fmt::print("\n");

    std::vector<std::any> v;

    v.push_back(std::any(c1));
    v.push_back(std::any(c2));
    v.push_back(std::any(d1));

    for (const auto& e : v)
    {
        if (e.type() == typeid(Cat))
        {
            fmt::print("e does contain a cat.\n");
            Cat c = std::any_cast<Cat>(e);
            fmt::print("c.my_name: {}\n", c.my_name);
        }
        else if (e.type() == typeid(Dog))
        {
            fmt::print("e does contain a dog.\n");
            Dog d = std::any_cast<Dog>(e);
            fmt::print("d.my_name: {}\n", d.my_name);
        }
    }
}