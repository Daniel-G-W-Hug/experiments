#include "use_TE_unique_ptr.hpp"

#include <vector>

void HD_TE_UNIQUE_PTR::demo()
{

    using namespace HD_TE_UNIQUE_PTR;

    fmt::print("\n\nUsing manual type erasure with std::unique_ptr...\n\n");

    using TE = TypeErased;

    Cat c1;
    Cat c2{"Pussy"};
    Dog d1{"Knut"};

    fmt::print("cat c1.my_name: {}\n", c1.my_name);
    fmt::print("cat c2.my_name: {}\n", c2.my_name);
    fmt::print("dog d1.my_name: {}\n", d1.my_name);
    fmt::print("\n");

    // TE c1 = TE{Cat()};
    // TE c2 = TE{Cat{"Pussy"}};
    // TE d1 = TE{Dog{"Knut"}};

    // fmt::print("cat c1.my_name: {}\n", c1.make_noise());
    // fmt::print("cat c2.my_name: {}\n", c2.make_noise());
    // fmt::print("dog d1.my_name: {}\n", d1.make_noise());
    // fmt::print("\n");

    // fmt::print("Size of Cat = {}\n", sizeof(Cat));
    // fmt::print("Size of Dog = {}\n", sizeof(Dog));
    // fmt::print("Size of TE = {}\n\n", sizeof(TE));
    // fmt::print("Size of c0 = {}\n", sizeof(c1));
    // fmt::print("Size of d0 = {}\n\n", sizeof(d1));

    // Cat* cp = new Cat;
    // fmt::print("Address of cp = {}\n", fmt::ptr(cp));
    // fmt::print("{}", cp->make_noise());
    // fmt::print(" My id is {}.\n", cp->id());
    // fmt::print(" Cat extra() is {}\n", cp->extra());
    // fmt::print(" cat_int is {}\n", cp->cat_int);
    // fmt::print(" cat_double is {}\n", cp->cat_double);
    // fmt::print(" cat_string is {}\n", cp->my_name);

    // TE* ap = new TE(*cp);
    // fmt::print("Address of ap = {}\n", fmt::ptr(ap));
    // fmt::print("{}", ap->make_noise());
    // fmt::print(" My id is {}.\n", ap->id());
    // fmt::print(" Cat extra() is {}\n", ap->extra());
    // fmt::print(" cat_data is {}\n", ap->cat_data());

    // Cat* c7 = reinterpret_cast<Cat*>(ap->clone(Cat()));
    // Cat c7 = ap->clone();
    // fmt::print("Address of c7 = {}\n", fmt::ptr(&c7));
    // fmt::print("{}", c7.make_noise());
    // fmt::print(" My id is {}.\n", c7.id());
    // fmt::print(" Cat extra() is {}\n", c7.extra());
    // fmt::print(" cat_int is {}\n", c7.cat_int);
    // fmt::print(" cat_double is {}\n", c7.cat_double);
    // fmt::print(" cat_string is {}\n", c7.cat_string);

    // TE a = Dog();
    // fmt::print("{}", a.make_noise());
    // fmt::print(" My id is {}.\n", a.id());

    std::vector<TE> ani;
    ani.push_back(TE{c1});
    ani.push_back(TE{c2});
    ani.push_back(TE{d1});

    for (const auto& e : ani)
    {
        if (e.id() == 1)
        {
            fmt::print("e does contain a cat.\n");
            // How to recover the Original?
            // Cat* c = e.clone<Cat>();
        }
        else if (e.id() == 2)
        {
            fmt::print("e does contain a dog.\n");
        }
        fmt::print("{}", e.make_noise());
        fmt::print(" My id is {}.\n", e.id());
    }
}