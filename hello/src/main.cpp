#include <iostream>

#include "hd/hd_keypress.hpp"

auto main(int argc, char* argv[]) -> int
{
    std::cout << "Hello World!\n";

    hd::cmdl_wait_for_enter();

    return 0;
}