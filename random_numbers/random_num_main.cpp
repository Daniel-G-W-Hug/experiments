#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <random>
#include <map>
#include <chrono>

int main() {

    using namespace std::chrono;

    auto t0 = high_resolution_clock::now();

    std::random_device rd;  // if left out, always the same sequence will be generated
    std::default_random_engine re(rd());
    std::uniform_int_distribution<int> uniform_dist(1,6);

    //int roll_dice = [](auto uniform_dist,auto re){return uniform_dist(re);};

    // roll the dice and store in map
    std::map<int,int> histogram;
    for (int i=0; i!=10000000; ++i) {
        int random_number = uniform_dist(re);
        //std::cout << "i = " << i << " dice = " << random_number << std::endl;
        ++histogram[random_number];
    }

    std::cout << std::endl;
    for (auto v : histogram) {
        std::cout << std::setw(2) << v.first << ": " << v.second << std::endl;
    }

    int min_val {std::numeric_limits<int>::max()};
    int max_val {0};
    for (auto v : histogram) {
        min_val = std::min(min_val, v.second);
        max_val = std::max(max_val, v.second);
    }
    std::cout << "\nmin_val = " << min_val << std::endl;
    std::cout << "max_val = " << max_val << '\n' << std::endl;

    const int num_stars_max_val = 25;
    for (auto v : histogram) {
        //std::cout << std::setw(2) << v.first << ": " << v.second << std::endl;
        std::cout << std::setw(2) << v.first << ": ";
        std::cout << std::string(v.second*num_stars_max_val/max_val,'*');
        std::cout << std::endl;
    }

    std::cout << std::endl;

    auto t1 = high_resolution_clock::now();
    auto time_required_ms = duration_cast<milliseconds>(t1-t0).count();
    std::cout << "Execution time was " << time_required_ms << " ms.\n" << std::endl;


    return 0;
}