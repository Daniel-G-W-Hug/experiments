
#include <iostream>
#include <utility> // for std::forward()
#include <vector>

#include "hd/hd_keypress.hpp"

template <typename CB>
class CountCalls
{
  private:

    CB callback;    // callback to call
    long calls = 0; // counter for calls
  public:

    CountCalls(CB cb) :
        callback(cb) {}
    template <typename... Args>
    auto operator()(Args&&... args)
    {
        ++calls;
        return callback(std::forward<Args>(args)...);
    }
    long count() const { return calls; }
};

// Auszug aus: Nicolai Josuttis. „C++17 - The Complete Guide.“ Apple Books.

using std::cout;

int main()
{

    std::vector v{31, 17, -9, 7, 12, 35, 6, 2, 0, 15, 97, 17, 24, -12};

    CountCalls sc([](auto x, auto y)
                  { return x > y; });

    std::sort(v.begin(), v.end(), std::ref(sc));
    std::cout << "sorted with " << sc.count() << " calls to sorting criterion.\n";

    hd::cmdl_wait_for_enter();

    return 0;
}
