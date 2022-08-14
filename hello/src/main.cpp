#include <iostream>

#include "hd/hd_keypress.hpp"

int main(int argc, char *argv[])
{
    std::cout << "Hello World!\n";

    hd::cmdl_wait_for_enter();

    return 0;
}