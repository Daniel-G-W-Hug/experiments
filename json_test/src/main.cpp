#include <exception>
#include <fstream>
#include <iostream>

#include "properties.hpp"

#include "hd/hd_keypress.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;

int main()
{

    try
    {
        std::ifstream i("../json_test/input/input.json");
        if (!i.good())
            throw std::runtime_error("Could not open input file.");
        auto j = nlohmann::ordered_json::parse(i);
        std::cout << j.dump(2) << "\n\n";

        for (auto& e : j.items())
        {
            // std::cout << "\n\nkey: " << e.key() << std::endl;
            // std::cout << "val: " << std::setw(4) << e.value() << '\n';

            if (e.key() == "window")
            {
                hd::window w;
                w.parse_from_json(e.value());

                std::cout << "window:\n"
                          << w << "\n\n";
            }
            else if (e.key() == "font")
            {
                hd::font font;
                font.parse_from_json(e.value());
                std::cout << "font:\n"
                          << font << "\n\n";
            }
            else if (e.key() == "circle")
            {
                hd::circle c;
                c.parse_from_json(e.value());
                std::cout << "circle:\n"
                          << c << "\n\n";
            }
            else if (e.key() == "rectangle")
            {
                hd::rectangle r;
                r.parse_from_json(e.value());
                std::cout << "rectangle:\n"
                          << r << "\n\n";
            }
            else
            {
                throw std::runtime_error("Unknown property in input file.");
            }
        }

    } // try
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    hd::cmdl_wait_for_enter();

    return 0;
}