#include <iostream>

#include "hd/hd_error.hpp"
#include "hd/hd_keypress.hpp"

// int main(int argc, char* argv[])
int main()
{
    std::cout << "Test error handling options.\n\n";

    hd::file_loc_msg("My message!");

    std::cout << "\n\n";

    int x{-5};
    hd::expect(x > 0, hd::Error_code::range_error);

    hd::cmdl_wait_for_enter();

    return 0;
}