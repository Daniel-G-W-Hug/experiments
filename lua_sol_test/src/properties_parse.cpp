#include "properties.hpp"
#include "properties_parse.hpp"

#include <ostream>

namespace hd {

////////////////////////////////////////////////////////////////////////////////
// parsing properties from lua_state
////////////////////////////////////////////////////////////////////////////////

window parse_window(sol::state& lua)
{
    window w;
    w.s.width = lua["window"]["size"]["width"];
    w.s.height = lua["window"]["size"]["height"];
    return w;
}

font parse_font(sol::state& lua)
{
    font f;
    f.ffile = lua["font"]["ffile"];
    f.fsize = lua["font"]["fsize"];
    f.col.r = lua["font"]["col_rgb"]["r"];
    f.col.g = lua["font"]["col_rgb"]["g"];
    f.col.b = lua["font"]["col_rgb"]["b"];
    return f;
}

circle parse_circle(sol::state& lua)
{
    circle c;
    c.name = lua["circle"]["name"];
    c.pos.x = lua["circle"]["position"]["x"];
    c.pos.y = lua["circle"]["position"]["y"];
    c.spd.sx = lua["circle"]["speed"]["sx"];
    c.spd.sy = lua["circle"]["speed"]["sy"];
    c.col.r = lua["circle"]["col_rgb"]["r"];
    c.col.g = lua["circle"]["col_rgb"]["g"];
    c.col.b = lua["circle"]["col_rgb"]["b"];
    c.radius = lua["circle"]["radius"];
    return c;
}

std::vector<circle> parse_circle_seq(sol::state& lua)
{
    std::vector<circle> v(sol::table(lua["circle_seq"]).size());
    for (int i = 0; i < v.size(); ++i) {
        v[i].name = lua["circle_seq"][i + 1]["name"];
        v[i].pos.x = lua["circle_seq"][i + 1]["position"]["x"];
        v[i].pos.y = lua["circle_seq"][i + 1]["position"]["y"];
        v[i].spd.sx = lua["circle_seq"][i + 1]["speed"]["sx"];
        v[i].spd.sy = lua["circle_seq"][i + 1]["speed"]["sy"];
        v[i].col.r = lua["circle_seq"][i + 1]["col_rgb"]["r"];
        v[i].col.g = lua["circle_seq"][i + 1]["col_rgb"]["g"];
        v[i].col.b = lua["circle_seq"][i + 1]["col_rgb"]["b"];
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
    r.col.r = lua["rectangle"]["col_rgb"]["r"];
    r.col.g = lua["rectangle"]["col_rgb"]["g"];
    r.col.b = lua["rectangle"]["col_rgb"]["b"];
    r.s.width = lua["rectangle"]["size"]["width"];
    r.s.height = lua["rectangle"]["size"]["height"];
    return r;
}

std::vector<rectangle> parse_rectangle_seq(sol::state& lua)
{
    std::vector<rectangle> v(sol::table(lua["rectangle_seq"]).size());
    for (int i = 0; i < v.size(); ++i) {
        v[i].name = lua["rectangle_seq"][i + 1]["name"];
        v[i].pos.x = lua["rectangle_seq"][i + 1]["position"]["x"];
        v[i].pos.y = lua["rectangle_seq"][i + 1]["position"]["y"];
        v[i].spd.sx = lua["rectangle_seq"][i + 1]["speed"]["sx"];
        v[i].spd.sy = lua["rectangle_seq"][i + 1]["speed"]["sy"];
        v[i].col.r = lua["rectangle_seq"][i + 1]["col_rgb"]["r"];
        v[i].col.g = lua["rectangle_seq"][i + 1]["col_rgb"]["g"];
        v[i].col.b = lua["rectangle_seq"][i + 1]["col_rgb"]["b"];
        v[i].s.width = lua["rectangle_seq"][i + 1]["size"]["width"];
        v[i].s.height = lua["rectangle_seq"][i + 1]["size"]["height"];
    }
    return v;
}

} // namespace hd
