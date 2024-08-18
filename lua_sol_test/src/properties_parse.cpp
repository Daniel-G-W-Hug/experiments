#include "properties.hpp"
#include "properties_parse.hpp"

#include <exception>
#include <ostream>

namespace hd {

////////////////////////////////////////////////////////////////////////////////
// parsing properties from lua_state
////////////////////////////////////////////////////////////////////////////////

window parse_window(sol::state& lua)
{
    window w;
    w.s.width = lua["window"]["size"]["width"].get_or(640);
    w.s.height = lua["window"]["size"]["height"].get_or(400);
    return w;
}

font parse_font(sol::state& lua)
{
    sol::optional<sol::table> font_exists = lua["font"];
    sol::optional<std::string> ffile_exists = lua["font"]["ffile"];
    if (font_exists && ffile_exists) {
        font f;
        f.ffile = lua["font"]["ffile"];
        f.fsize = lua["font"]["fsize"].get_or(12);
        f.col.r = lua["font"]["col_rgb"]["r"].get_or(255);
        f.col.g = lua["font"]["col_rgb"]["g"].get_or(255);
        f.col.b = lua["font"]["col_rgb"]["b"].get_or(255);
        return f;
    }
    else {
        throw std::runtime_error("parse_font: 'font' and 'ffile' must be specified.\n");
    }
}

circle parse_circle(sol::state& lua)
{
    circle c;
    c.name = lua["circle"]["name"];
    c.pos.x = lua["circle"]["position"]["x"];
    c.pos.y = lua["circle"]["position"]["y"];
    c.spd.sx = lua["circle"]["speed"]["sx"];
    c.spd.sy = lua["circle"]["speed"]["sy"];
    c.col.r = lua["circle"]["col_rgb"]["r"].get_or(255);
    c.col.g = lua["circle"]["col_rgb"]["g"].get_or(255);
    c.col.b = lua["circle"]["col_rgb"]["b"].get_or(255);
    c.radius = lua["circle"]["radius"];
    return c;
}

std::vector<circle> parse_circle_seq(sol::state& lua)
{
    std::vector<circle> v(sol::table(lua["circle_seq"]).size());
    for (size_t i = 0; i < v.size(); ++i) {
        v[i].name = lua["circle_seq"][i + 1]["name"];
        v[i].pos.x = lua["circle_seq"][i + 1]["position"]["x"];
        v[i].pos.y = lua["circle_seq"][i + 1]["position"]["y"];
        v[i].spd.sx = lua["circle_seq"][i + 1]["speed"]["sx"];
        v[i].spd.sy = lua["circle_seq"][i + 1]["speed"]["sy"];
        v[i].col.r = lua["circle_seq"][i + 1]["col_rgb"]["r"].get_or(255);
        v[i].col.g = lua["circle_seq"][i + 1]["col_rgb"]["g"].get_or(255);
        v[i].col.b = lua["circle_seq"][i + 1]["col_rgb"]["b"].get_or(255);
        v[i].radius = lua["circle_seq"][i + 1]["radius"];
    }
    return v;
}

rectangle parse_rectangle(sol::state& lua)
{
    rectangle r;
    r.name = lua["rectangle"]["name"];
    r.pos.x = lua["rectangle"]["position"]["x"];
    r.pos.y = lua["rectangle"]["position"]["y"];
    r.spd.sx = lua["rectangle"]["speed"]["sx"];
    r.spd.sy = lua["rectangle"]["speed"]["sy"];
    r.col.r = lua["rectangle"]["col_rgb"]["r"].get_or(255);
    r.col.g = lua["rectangle"]["col_rgb"]["g"].get_or(255);
    r.col.b = lua["rectangle"]["col_rgb"]["b"].get_or(255);
    r.s.width = lua["rectangle"]["size"]["width"];
    r.s.height = lua["rectangle"]["size"]["height"];
    return r;
}

std::vector<rectangle> parse_rectangle_seq(sol::state& lua)
{
    std::vector<rectangle> v(sol::table(lua["rectangle_seq"]).size());
    for (size_t i = 0; i < v.size(); ++i) {
        v[i].name = lua["rectangle_seq"][i + 1]["name"];
        v[i].pos.x = lua["rectangle_seq"][i + 1]["position"]["x"];
        v[i].pos.y = lua["rectangle_seq"][i + 1]["position"]["y"];
        v[i].spd.sx = lua["rectangle_seq"][i + 1]["speed"]["sx"];
        v[i].spd.sy = lua["rectangle_seq"][i + 1]["speed"]["sy"];
        v[i].col.r = lua["rectangle_seq"][i + 1]["col_rgb"]["r"].get_or(255);
        v[i].col.g = lua["rectangle_seq"][i + 1]["col_rgb"]["g"].get_or(255);
        v[i].col.b = lua["rectangle_seq"][i + 1]["col_rgb"]["b"].get_or(255);
        v[i].s.width = lua["rectangle_seq"][i + 1]["size"]["width"];
        v[i].s.height = lua["rectangle_seq"][i + 1]["size"]["height"];
    }
    return v;
}

} // namespace hd
