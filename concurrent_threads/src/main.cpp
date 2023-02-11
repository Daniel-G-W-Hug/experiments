#include <chrono>
#include <iostream>
#include <mutex>

#ifdef WIN32
#include <thread>
#else
// version that uses local jthread instance, in case not yet available in <thread> in C++20 mode (e.g. clang++)
// #include "jthread/source/jthread.hpp"
#include "jthread.hpp"
#endif

#include "fmt/format.h"
#include "fmt/ostream.h" // for printing thread id via operator << (fmt::streamed)
#include "fmt/ranges.h"

int main(int argc, char *argv[])
{

    // std::cout << "Hello parallel world!";
    fmt::print("Hello parallel world!\n");

    std::mutex mtx;

    std::jthread t([&] {
        fmt::print("separate: id={}\n", fmt::streamed(std::this_thread::get_id()));
        for (size_t s = 0; s < 25; ++s)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            {
                std::lock_guard g(mtx);
                fmt::print("--- (separate), s={:2}\n", s);
                // std::cout << "--- (separate)" << std::endl;
            }
        }
    });

    fmt::print("main: id={}\n", fmt::streamed(std::this_thread::get_id()));
    for (size_t m = 0; m < 10; ++m)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        {
            std::lock_guard g(mtx);
            fmt::print("*** (main),     m={:2}\n", m);
            // std::cout << "*** (main)" << std::endl;
        }
    }

    return 0;
}