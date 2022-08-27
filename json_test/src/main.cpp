#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include "hd/hd_keypress.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;

// redefine MACRO since original macro uses nlohmann::json instead of json
#if defined(NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE)
#undef NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE
#endif
#define NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Type, __VA_ARGS__...)                                                                                         \
    inline void to_json(json& nlohmann_json_j, const Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) } \
    inline void from_json(const json& nlohmann_json_j, Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, __VA_ARGS__)) }

namespace hd
{

////////////////////////////////////////////////////////////////////////////////
// elementary json objects for non-trivial struct-like properties
////////////////////////////////////////////////////////////////////////////////

struct size
{
    int width;  // width in pixels
    int height; // height in pixels
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(size, width, height)

std::ostream& operator<<(std::ostream& os, const size& s)
{
    os << s.width << ", " << s.height;
    return os;
}

struct color_rgb
{
    int r{0}; // red [0..255]
    int g{0}; // green [0..255]
    int b{0}; // blue [0..255]
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(color_rgb, r, g, b)

std::ostream& operator<<(std::ostream& os, const color_rgb& c)
{
    os << c.r << ", " << c.g << ", " << c.b;
    return os;
}

struct position
{
    int x{0}; // x position in pixels
    int y{0}; // y position in pixels
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(position, x, y)

std::ostream& operator<<(std::ostream& os, const position& p)
{
    os << p.x << ", " << p.y;
    return os;
}

struct speed
{
    float sx{0.0f}; // x speed in pixels per frame
    float sy{0.0f}; // y speed in pixels per frame
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(speed, sx, sy)

std::ostream& operator<<(std::ostream& os, const speed& s)
{
    os << s.sx << ", " << s.sy;
    return os;
}

////////////////////////////////////////////////////////////////////////////////
// properties for use in application - typically combined properties
////////////////////////////////////////////////////////////////////////////////

struct window
{
    std::string get_id() const { return "window"; }
    size s;
};

std::ostream& operator<<(std::ostream& os, const window& w)
{
    os << "size: " << w.s;
    return os;
}

struct font
{
    std::string get_id() const { return "font"; }
    std::string ffile{}; // file name of font file (typically *.ttf)
    int fsize{12};       // font size in pts
    color_rgb col;       // font color
};

std::ostream& operator<<(std::ostream& os, const font& f)
{
    os << "ffile: " << f.ffile << std::endl;
    os << "fsize: " << f.fsize << std::endl;
    os << "color_rgb: " << f.col;
    return os;
}

struct circle
{
    std::string get_id() const { return "circle"; }
    std::string name{}; // display name
    position pos;       // position
    speed spd;          // speed
    color_rgb col;      // fill color
    int radius{0};      // radius of circle in pixels
};

std::ostream& operator<<(std::ostream& os, const circle& c)
{
    os << "name: " << c.name << std::endl;
    os << "pos: " << c.pos << std::endl;
    os << "spd: " << c.spd << std::endl;
    os << "color_rgb: " << c.col << std::endl;
    os << "radius: " << c.radius;
    return os;
}

struct rectangle
{
    std::string get_id() const { return "rectangle"; }
    std::string name{}; // display name
    position pos;       // position
    speed spd;          // speed
    color_rgb col;      // fill color
    size s;             // size of rectangle in pixels
};

std::ostream& operator<<(std::ostream& os, const rectangle& r)
{
    os << "name: " << r.name << std::endl;
    os << "pos: " << r.pos << std::endl;
    os << "spd: " << r.spd << std::endl;
    os << "color_rgb: " << r.col << std::endl;
    os << "size: " << r.s;
    return os;
}

} // namespace hd

int main()
{

    try
    {

        std::ifstream i("../json_test/src/input.json");
        auto j = nlohmann::ordered_json::parse(i);
        std::cout << j.dump(2) << "\n\n";

        for (auto& e : j.items())
        {
            // std::cout << "\n\nkey: " << e.key() << std::endl;
            // std::cout << "val: " << std::setw(4) << e.value() << '\n';

            if (e.key() == "window")
            {
                hd::window w;
                w.s = e.value().at("size");
                std::cout << "window:\n"
                          << w << "\n\n";
            }
            else if (e.key() == "font")
            {
                hd::font font;
                font.ffile = e.value().at("ffile");
                font.fsize = e.value().at("fsize");
                font.col = e.value().at("color_rgb");
                std::cout << "font:\n"
                          << font << "\n\n";
            }
            else if (e.key() == "circle")
            {
                hd::circle c;
                c.name = e.value().at("name");
                c.pos = e.value().at("position");
                c.spd = e.value().at("speed");
                c.col = e.value().at("color_rgb");
                c.radius = e.value().at("radius");
                std::cout << "circle:\n"
                          << c << "\n\n";
            }
            else if (e.key() == "rectangle")
            {
                hd::rectangle r;
                r.name = e.value().at("name");
                r.pos = e.value().at("position");
                r.spd = e.value().at("speed");
                r.col = e.value().at("color_rgb");
                r.s = e.value().at("size");
                std::cout << "rectangle:\n"
                          << r << "\n\n";
            }
            else
            {
                throw std::runtime_error("Unknown property in input file.\n");
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