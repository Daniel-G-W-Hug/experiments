#include "fmt/format.h"
#include "fmt/ranges.h"

#include "boost/circular_buffer.hpp"

#include "hd/hd_keypress.hpp"

#include <iostream>

int main()
{

    //[circular_buffer_example_2
    // Create a circular buffer with a capacity for 3 integers.
    boost::circular_buffer<int> cb(5);

    // Insert three elements into the buffer.
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);

    // int a = cb[0]; // a == 1
    // int b = cb[1]; // b == 2
    // int c = cb[2]; // c == 3

    fmt::print("initial cb: {}\n", cb);

    fmt::print("cb capacity: {}, size: {}, full: {}, empty: {}, front: {}, back: {}\n\n",
               cb.capacity(), cb.size(), cb.full(), cb.empty(), cb.front(), cb.back());

    // The buffer is full now, so pushing subsequent
    // elements will overwrite the front-most elements.

    cb.push_back(4); // Overwrite 1 with 4.
    cb.push_back(5); // Overwrite 2 with 5.

    // The buffer now contains 3, 4 and 5.
    // a = cb[0]; // a == 3
    // b = cb[1]; // b == 4
    // c = cb[2]; // c == 5

    fmt::print("after overwrite cb: {}\n", cb);
    fmt::print("cb capacity: {}, size: {}, full: {}, empty: {}, front: {}, back: {}\n\n",
               cb.capacity(), cb.size(), cb.full(), cb.empty(), cb.front(), cb.back());

    // Elements can be popped from either the front or the back.
    cb.pop_back();  // 5 is removed.
    cb.pop_front(); // 3 is removed.

    // Leaving only one element with value = 4.
    // int d = cb[0]; // d == 4

    fmt::print("after pop_front & pop_back cb: {}\n", cb);
    fmt::print("cb capacity: {}, size: {}, full: {}, empty: {}, front: {}, back: {}\n\n",
               cb.capacity(), cb.size(), cb.full(), cb.empty(), cb.front(), cb.back());

    hd::cmdl_wait_for_enter();

    return 0;
}
