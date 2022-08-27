#include "properties.hpp"

namespace hd
{

////////////////////////////////////////////////////////////////////////////////
// stream operators for json objects
////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, const size& s)
{
    os << s.width << ", " << s.height;
    return os;
}

std::ostream& operator<<(std::ostream& os, const color_rgb& c)
{
    os << c.r << ", " << c.g << ", " << c.b;
    return os;
}

std::ostream& operator<<(std::ostream& os, const position& p)
{
    os << p.x << ", " << p.y;
    return os;
}

std::ostream& operator<<(std::ostream& os, const speed& s)
{
    os << s.sx << ", " << s.sy;
    return os;
}

std::ostream& operator<<(std::ostream& os, const window& w)
{
    os << "size: " << w.s;
    return os;
}

std::ostream& operator<<(std::ostream& os, const font& f)
{
    os << "ffile: " << f.ffile << std::endl;
    os << "fsize: " << f.fsize << std::endl;
    os << "color_rgb: " << f.col;
    return os;
}

std::ostream& operator<<(std::ostream& os, const circle& c)
{
    os << "name: " << c.name << std::endl;
    os << "pos: " << c.pos << std::endl;
    os << "spd: " << c.spd << std::endl;
    os << "color_rgb: " << c.col << std::endl;
    os << "radius: " << c.radius;
    return os;
}

std::ostream& operator<<(std::ostream& os, const rectangle& r)
{
    os << "name: " << r.name << std::endl;
    os << "pos: " << r.pos << std::endl;
    os << "spd: " << r.spd << std::endl;
    os << "color_rgb: " << r.col << std::endl;
    os << "size: " << r.s;
    return os;
}

////////////////////////////////////////////////////////////////////////////////
// parsing properties
////////////////////////////////////////////////////////////////////////////////

void window::parse_from_json(json const& j)
{
    s = j.at("size");
}

void font::parse_from_json(json const& j)
{
    ffile = j.at("ffile");
    fsize = j.at("fsize");
    col = j.at("color_rgb");
}

void circle::parse_from_json(json const& j)
{
    name = j.at("name");
    pos = j.at("position");
    spd = j.at("speed");
    col = j.at("color_rgb");
    radius = j.at("radius");
}

void rectangle::parse_from_json(json const& j)
{
    name = j.at("name");
    pos = j.at("position");
    spd = j.at("speed");
    col = j.at("color_rgb");
    s = j.at("size");
}

} // namespace hd
