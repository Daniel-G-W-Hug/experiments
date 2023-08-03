#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <string_view>

#include "fmt/format.h"
#include "fmt/ostream.h"
#include "fmt/ranges.h"

#include "di8joy.hpp"
#include "di8joy_json_io.hpp"

#include "hd/hd_keypress.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

template <typename Map_t>
void print_map(std::string_view prefix, const Map_t& m)
{
    fmt::print("{} =\n{{\n", prefix);
    for (const auto& [key, value] : m)
    {
        fmt::print("    \"{}\": {}\n", key, value);
    }
    fmt::print("}}\n");
}

int main()
{

    // create data structure filled with default values to overwrite from input

    // using button_map = std::map<std::string, int>; // map button_name to button index

    // button_map bm{{"B1", 1}, {"B2", 2}, {"B3", 3}};

    // // fmt::print("{} = {}\n", "bm", bm);
    // print_map("bm", bm);

    // json j_map(bm);

    // std::cout << std::setw(4) << j_map << '\n';

    try
    {
        std::ifstream i("../json_io/input/input.json");
        if (!i.good())
            throw std::runtime_error("Could not open input file.");
        auto j = json::parse(i);
        // std::cout << j.dump(2) << "\n\n";

        // read device section
        for (auto& e : j["device"])
        {
            hd::js::dev_id dev = e.get<hd::js::dev_id>();
            std::cout << "joystick:\n"
                      << dev << "\n";
        }

        // read device capability section
        for (auto& e : j["device_capabilities"])
        {
            unsigned int curr_id = e["a_id"];
            hd::js::dev_cap dev_cap = e["capability"].get<hd::js::dev_cap>();
            std::cout << "capability:\n";
            std::cout << "a_id: " << curr_id << ", ";
            std::cout << dev_cap << "\n";
        }

        // read button mapping section
        for (auto& e : j["device_map_buttons"])
        {
            unsigned int curr_id = e["a_id"];

            std::cout << "button:\n";
            for (auto& s_e : e["buttons"])
            {
                hd::js::dev_button dev_button = s_e.get<hd::js::dev_button>();
                std::cout << "a_id: " << curr_id << ", ";
                std::cout << dev_button;
            }
            std::cout << "\n";
        }

        // writing to stdout

        json j2;
        std::cout << "\n\nj2:";
        j2["device"].push_back(hd::js::dev_id{});
        j2["device"].push_back(hd::js::dev_id{});
        json jh;
        jh["a_id"] = 0;
        jh["capability"] = hd::js::dev_cap{};
        j2["device_capabilities"].push_back(jh);
        json jh1;
        jh1["a_id"] = 1;
        jh1["capability"] = hd::js::dev_cap{};
        j2["device_capabilities"].push_back(jh1);
        json jb;
        jb["a_id"] = 2;
        jb["buttons"].push_back(hd::js::dev_button{});
        jb["buttons"].push_back(hd::js::dev_button{});
        j2["device_map_buttons"].push_back(jb);

        std::cout << j2.dump(2) << "\n\n";

    } // try

    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    hd::cmdl_wait_for_enter();

    return 0;
}