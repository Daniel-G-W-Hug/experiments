#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "json_properties.hpp"

#include "hd/hd_keypress.hpp"

void id_print(hd::property const* p)
{
    std::cout << "p->get_id() = " << p->get_id() << std::endl;
}

std::vector<hd::property*> read_properties(std::string const& fname)
{

    std::vector<hd::property*> v;

    try
    {
        std::ifstream i(fname);
        if (!i.good())
            throw std::runtime_error("Could not open input file.");
        auto j = nlohmann::ordered_json::parse(i);
        std::cout << j.dump(2) << "\n\n";

        for (auto& e : j.items())
        {
            // std::cout << "\n\nkey: " << e.key() << std::endl;
            // std::cout << "val: " << std::setw(4) << e.value() << "\n\n";

            if (e.key() == "window")
            {
                hd::window* w = new hd::window;
                w->parse_from_json(e.value());

                std::cout << "window:\n"
                          << *w << "\n\n";

                v.push_back(w);
            }
            else if (e.key() == "font")
            {
                hd::font* f = new hd::font;
                f->parse_from_json(e.value());
                std::cout << "font:\n"
                          << *f << "\n\n";
                v.push_back(f);
            }
            else if (e.key() == "circles")
            {
                for (auto& elem : e.value())
                {
                    hd::circle* c = new hd::circle;
                    c->parse_from_json(elem["circle"]);
                    std::cout << "circle:\n"
                              << *c << "\n\n";
                    v.push_back(c);
                }
            }
            else if (e.key() == "circle")
            {
                hd::circle* c = new hd::circle;
                c->parse_from_json(e.value());
                std::cout << "circle:\n"
                          << *c << "\n\n";
                v.push_back(c);
            }
            else if (e.key() == "rectangles")
            {
                for (auto& elem : e.value())
                {
                    hd::rectangle* r = new hd::rectangle;
                    r->parse_from_json(elem["rectangle"]);
                    std::cout << "rectangle:\n"
                              << *r << "\n\n";
                    v.push_back(r);
                }
            }
            else if (e.key() == "rectangle")
            {
                hd::rectangle* r = new hd::rectangle;
                r->parse_from_json(e.value());
                std::cout << "rectangle:\n"
                          << *r << "\n\n";
                v.push_back(r);
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

    return v;
}

int main()
{

    std::vector<hd::property*> v = read_properties("../json_test/input/input.json");

    for (auto& p : v)
    {
        id_print(p);

        if (p->get_id() == "window")
        {
            hd::window* w = dynamic_cast<hd::window*>(p);
            std::cout << *w << "\n\n";
        }
        else if (p->get_id() == "font")
        {
            hd::font* f = dynamic_cast<hd::font*>(p);
            std::cout << *f << "\n\n";
        }
        else if (p->get_id() == "circle")
        {
            hd::circle* c = dynamic_cast<hd::circle*>(p);
            std::cout << *c << "\n\n";
        }
        else if (p->get_id() == "rectangle")
        {
            hd::rectangle* r = dynamic_cast<hd::rectangle*>(p);
            std::cout << *r << "\n\n";
        }
    }

    hd::cmdl_wait_for_enter();

    return 0;
}