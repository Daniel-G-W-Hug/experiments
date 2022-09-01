#ifndef HD_JSON_PROPERTIES_HPP
#define HD_JSON_PROPERTIES_HPP

#include <string>
using namespace std::literals::string_literals;

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
std::ostream& operator<<(std::ostream& os, const size& s);


struct color_rgb
{
    int r{0}; // red [0..255]
    int g{0}; // green [0..255]
    int b{0}; // blue [0..255]
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(color_rgb, r, g, b)
std::ostream& operator<<(std::ostream& os, const color_rgb& c);

struct position
{
    int x{0}; // x position in pixels
    int y{0}; // y position in pixels
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(position, x, y)
std::ostream& operator<<(std::ostream& os, const position& p);


struct speed
{
    float sx{0.0f}; // x speed in pixels per frame
    float sy{0.0f}; // y speed in pixels per frame
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(speed, sx, sy)
std::ostream& operator<<(std::ostream& os, const speed& s);

////////////////////////////////////////////////////////////////////////////////
// properties for use in application - typically combined properties
////////////////////////////////////////////////////////////////////////////////

struct window
{
    size s;

    void parse_from_json(json const& j);
    static std::string get_id() { return "window"s; }
};

std::ostream& operator<<(std::ostream& os, const window& w);


struct font
{
    std::string ffile{}; // file name of font file (typically *.ttf)
    int fsize{12};       // font size in pts
    color_rgb col;       // font color

    void parse_from_json(json const& j);
    static std::string get_id() { return "font"s; }
};

std::ostream& operator<<(std::ostream& os, const font& f);


struct circle
{
    std::string name{}; // display name
    position pos;       // position
    speed spd;          // speed
    color_rgb col;      // fill color
    int radius{0};      // radius of circle in pixels

    void parse_from_json(json const& j);
    static std::string get_id() { return "circle"s; }
};

std::ostream& operator<<(std::ostream& os, const circle& c);


struct rectangle
{
    std::string name{}; // display name
    position pos;       // position
    speed spd;          // speed
    color_rgb col;      // fill color
    size s;             // size of rectangle in pixels

    void parse_from_json(json const& j);
    static std::string get_id() { return "rectangle"s; }
};

std::ostream& operator<<(std::ostream& os, const rectangle& r);

} // namespace hd

#endif // HD_JSON_PROPERTIES_HPP