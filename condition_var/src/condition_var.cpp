
#include "fmt/format.h"
#include "fmt/ostream.h" // enable printing of thread::id via operator<<()
#include "fmt/ranges.h"  // support printing of (nested) containers & tuples

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <string>
#include <thread>

// conditionally include, if not yet available in compiler in c++23 mode
#include "jthread.hpp"

#include "hd/hd_keypress.hpp"

using namespace std::chrono_literals;

std::mutex mtx;
std::condition_variable condVar;
std::string data{"garbage data - not ready for use by workers"};

bool dataReady{false};

void waitingForWork(std::stop_token stk)
{
    std::thread::id my_id = std::this_thread::get_id();
    fmt::print("id: {}, waiting.\n", fmt::streamed(my_id));
    std::unique_lock<std::mutex> lck(mtx);
    condVar.wait(lck, [] { return dataReady; });
    fmt::print("id: {}, running. Data = {}\n", fmt::streamed(my_id), data);

    while (!stk.stop_requested()) {
        fmt::print("id: {}, idle waiting for stop.\n", fmt::streamed(my_id));
        std::this_thread::sleep_for(200ms);
    }

    fmt::print("id: {}, stop initiated - returning.\n", fmt::streamed(my_id));

    return;
}

void setDataReady(std::stop_token stk)
{
    std::thread::id my_id = std::this_thread::get_id();
    data = "data made ready for use";
    fmt::print("id: {}, data prepared. Released for use by workers.\n",
               fmt::streamed(my_id));
    {
        std::lock_guard<std::mutex> lck(mtx);
        dataReady = true;
    }
    condVar.notify_all();

    while (!stk.stop_requested()) {
        fmt::print("id: {}, idle waiting for stop.\n", fmt::streamed(my_id));
        std::this_thread::sleep_for(200ms);
    }

    fmt::print("id: {}, stop initiated - returning.\n", fmt::streamed(my_id));

    return;
}

void stop_cb_notifier()
{
    std::thread::id my_id = std::this_thread::get_id();
    fmt::print("\nid: {}, stop requested and stop callback notifier called.\n\n",
               fmt::streamed(my_id));
}

int main()
{
    fmt::print("\n");

    fmt::print("id: {} is main thread.\n\n", fmt::streamed(std::this_thread::get_id()));

    std::stop_source st_src;
    std::stop_token st_tok{st_src.get_token()};
    std::stop_callback st_cb{st_tok, stop_cb_notifier};

    std::jthread t0(setDataReady, st_tok);
    std::jthread t1(waitingForWork, st_tok);
    std::jthread t2(waitingForWork, st_tok);

    std::this_thread::sleep_for(1s);
    st_src.request_stop();

    // char c;
    // std::cin >> c;
    // if (c == 's') {
    //   st_src.request_stop();
    // }

    t0.join();
    t1.join();
    t2.join();

    fmt::print("\n");

    hd::cmdl_wait_for_enter();

    return 0;
}