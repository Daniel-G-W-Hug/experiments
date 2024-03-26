#pragma once

#include <ostream>
#include <string>
using namespace std::string_literals;

namespace hd {

////////////////////////////////////////////////////////////////////////////////
// elementary lua objects for non-trivial struct-like properties
////////////////////////////////////////////////////////////////////////////////

struct size {
    int width;  // width in pixels
    int height; // height in pixels
};
std::ostream& operator<<(std::ostream& os, const size& s);


struct col_rgb {
    int r{0}; // red [0..255]
    int g{0}; // green [0..255]
    int b{0}; // blue [0..255]
};
std::ostream& operator<<(std::ostream& os, const col_rgb& c);

struct position {
    int x{0}; // x position in pixels
    int y{0}; // y position in pixels
};
std::ostream& operator<<(std::ostream& os, const position& p);


struct speed {
    float sx{0.0f}; // x speed in pixels per frame
    float sy{0.0f}; // y speed in pixels per frame
};
std::ostream& operator<<(std::ostream& os, const speed& s);

////////////////////////////////////////////////////////////////////////////////
// properties for use in application - typically combined properties
////////////////////////////////////////////////////////////////////////////////

struct window {
    size s;

    static std::string get_id() { return "window"s; }
};
std::ostream& operator<<(std::ostream& os, const window& w);


struct font {
    std::string ffile{}; // file name of font file (typically *.ttf)
    int fsize{12};       // font size in pts
    col_rgb col;         // font color

    static std::string get_id() { return "font"s; }
};
std::ostream& operator<<(std::ostream& os, const font& f);


struct circle {
    std::string name{}; // display name
    position pos;       // position
    speed spd;          // speed
    col_rgb col;        // fill color
    int radius{0};      // radius of circle in pixels

    static std::string get_id() { return "circle"s; }
};
std::ostream& operator<<(std::ostream& os, const circle& c);


struct rectangle {
    std::string name{}; // display name
    position pos;       // position
    speed spd;          // speed
    col_rgb col;        // fill color
    size s;             // size of rectangle in pixels

    static std::string get_id() { return "rectangle"s; }
};

std::ostream& operator<<(std::ostream& os, const rectangle& r);


} // namespace hd
