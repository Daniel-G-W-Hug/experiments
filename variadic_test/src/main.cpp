#include "variadic.hpp"

#include "hd/hd_keypress.hpp"

using namespace std::string_literals;

int main()
{

    variadic_print("initial"s);
    variadic_print("initial"s, "test1"s);
    variadic_print("initial"s, "test1"s, "test2"s);

    hd::cmdl_wait_for_enter();

    return 0;
}