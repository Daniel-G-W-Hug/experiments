#include "properties.hpp"

namespace hd {

////////////////////////////////////////////////////////////////////////////////
// stream operators for properties
////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, const size& s)
{
    os << s.width << ", " << s.height;
    return os;
}

std::ostream& operator<<(std::ostream& os, const col_rgb& c)
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
    os << "ffile: \"" << f.ffile << "\"" << std::endl;
    os << "fsize: " << f.fsize << std::endl;
    os << "col_rgb: " << f.col;
    return os;
}

std::ostream& operator<<(std::ostream& os, const circle& c)
{
    os << "name: \"" << c.name << "\"" << std::endl;
    os << "pos: " << c.pos << std::endl;
    os << "spd: " << c.spd << std::endl;
    os << "col_rgb: " << c.col << std::endl;
    os << "radius: " << c.radius;
    return os;
}

std::ostream& operator<<(std::ostream& os, const rectangle& r)
{
    os << "name: \"" << r.name << "\"" << std::endl;
    os << "pos: " << r.pos << std::endl;
    os << "spd: " << r.spd << std::endl;
    os << "col_rgb: " << r.col << std::endl;
    os << "size: " << r.s;
    return os;
}

} // namespace hd
