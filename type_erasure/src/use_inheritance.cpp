#include "use_inheritance.hpp"

#include <vector>

void HD_INHERITANCE::demo()
{

    using namespace HD_INHERITANCE;

    Cat c1;
    Cat c2{"Pussy"};
    Dog d1{"Knut"};

    fmt::print("\n\nUsing classical inheritance...\n\n");
    fmt::print("cat c1.my_name: {}\n", c1.my_name);
    fmt::print("cat c2.my_name: {}\n", c2.my_name);
    fmt::print("dog d1.my_name: {}\n", d1.my_name);
    fmt::print("\n");

    std::vector<noisy_animal_with_id*> v;

    // implicit conversion to noisy_animal_with_id*
    v.push_back(&c1);
    v.push_back(&c2);
    v.push_back(&d1);

    for (const auto& e : v)
    {
        if (Cat* c = dynamic_cast<Cat*>(e)) // if (c != nullptr) e contains a Cat
        {
            fmt::print("e does contain a cat.\n");
            fmt::print("c->my_name: {}\n", c->my_name);
        }
        else if (Dog* d = dynamic_cast<Dog*>(e)) // if (d != nullptr) e contains a dog
        {
            fmt::print("e does contain a dog.\n");
            fmt::print("d->my_name: {}\n", d->my_name);
        }
    }
}