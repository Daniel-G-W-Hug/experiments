#include <iostream>
#include <ranges>
#include <vector>

#include "hd/hd_keypress.hpp"

int main()
{
    std::vector v{0, 1, 2};

    std::cout << "If filter is a no-op, i.e. 'predicate = true' and if transform "
                 "is an identity-op, i.e. 'return value',\n";
    std::cout << "both operations should be equivalent, i.e. cause the same call "
                 "sequence and result. But they don't.\n";
    std::cout << "While the result is the same, the generated call sequence "
                 "isn't. This seems unexpected.\n\n";

    std::cout << "Sequence: v | filter | transform:\n";

    auto always_true = [](int i) { std::cout << "filter: " << i << "\n"; return true; };

    auto return_arg = [](int i) { std::cout << "transform: " << i << "\n"; return i; };

    auto rng1 = v | std::views::filter(always_true) | std::views::transform(return_arg);

    // std::cout << rng1 << "\n\n";
    std::cout << "[ ";
    for (auto const &e : rng1)
    {
        std::cout << e << ", ";
    }
    std::cout << "]\n\n";

    std::cout << "Sequence: v | transform | filter:\n";
    // not functionally equivalent when not no-op/identity, but still useful for
    // checking sequence of generated calls
    auto rng2 = v | std::views::transform([](int i) {
                std::cout << "transform: " << i << "\n";
                return i; }) |
                std::views::filter([](int i) {
                std::cout << "filter: " << i << "\n";
                return true; });
    // std::cout << rng2 << "\n\n";
    std::cout << "[ ";
    for (auto const &e : rng2)
    {
        std::cout << e << ", ";
    }
    std::cout << "]\n\n";

    std::cout << "Sequence: v | transform | transform:\n";
    auto rng3 = v | std::views::transform([](int i) {
                std::cout << "transform: " << i << "\n";
                return i; }) |
                std::views::transform([](int i) {
                std::cout << "transform: " << i << "\n";
                return i; });
    std::cout << "[ ";
    for (auto const &e : rng3)
    {
        std::cout << e << ", ";
    }
    std::cout << "]\n\n";
    // fmt::print("rng6 = {}\n\n",rng3);  // fmt only works after conversion to
    // container, but not directly for views

    std::cout << "Sequence: v | filter | filter:\n";
    auto rng4 = v | std::views::filter([](int i) {
                std::cout << "filter: " << i << "\n";
                return true; }) |
                std::views::filter([](int i) {
                std::cout << "filter: " << i << "\n";
                return true; });
    std::cout << "[ ";
    for (auto const &e : rng4)
    {
        std::cout << e << ", ";
    }
    std::cout << "]\n\n";
    // fmt::print("rng4 = {}\n\n",rng4);

    std::cout
        << "\nUnrelated issue? (that however let to discovering the above):\n\n";
    std::cout << "Unexpected call sequence. Output mixed in between filter and "
                 "transform calls (lazy + impl. of operator<< ?):\n";
    auto rng10 = v | std::views::filter([](int i) {
                 std::cout << "filter: " << i << "\n"; /*return i % 2 == 0;*/
                 return true; }) |
                 std::views::transform([](int i) {
                 std::cout << "transform: " << i << "\n"; /* return i * 2;*/
                 return i; });
    std::cout << "[ ";
    for (auto const &e : rng10)
    {
        std::cout << e << ", ";
    }
    std::cout << "]\n\n";

    std::cout << "This yields a more expected output sequence:\n";
    auto rng11 = v | std::views::filter([](int i) {
                 std::cout << "filter: " << i << "\n"; /*return i % 2 == 0;*/
                 return true; }) |
                 std::views::transform([](int i) {
                 std::cout << "transform: " << i << "\n"; /* return i * 2;*/
                 return i; });
    std::cout << "[ ";
    for (auto const &e : rng11)
    {
        std::cout << e << ", ";
    }
    std::cout << "]\n\n";

    hd::cmdl_wait_for_enter();

    return 0;
}