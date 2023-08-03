#include "di8joy_json_io.hpp"
#include "hd/hd_string_trim.hpp"

namespace hd
{

////////////////////////////////////////////////////////////////////////////////
// stream operators for json objects and for parsing from json
// (mainly for debugging)
////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const js::dev_id& dev)
{
    os << "a_id: " << dev.a_id << ", ";
    os << "a_index: " << dev.a_index << ", ";
    os << "a_name: " << dev.a_name << ", ";
    os << "sys_name: " << dev.sys_name << ", ";
    os << "sys_product_id: " << dev.sys_product_id << ", ";
    os << "sys_vendor_id: " << dev.sys_vendor_id << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const js::dev_cap& c)
{
    os << "axis_flags: " << std::bitset<8>(c.axis_flags) << ", ";
    os << "axis_string: " << c.axis_string << ", ";
    os << "nAxis: " << c.nAxis << ", ";
    os << "nButton: " << c.nButton << ", ";
    os << "nPOV: " << c.nPOV << ", " << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const js::dev_button& b)
{
    os << "index: " << b.index << ", ";
    os << "name: " << b.name << std::endl;
    return os;
}

} // namespace hd
