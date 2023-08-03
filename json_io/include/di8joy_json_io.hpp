#ifndef HD_DI8JOY_JSON_IO_HPP
#define HD_DI8JOY_JSON_IO_HPP

#include "di8joy.hpp"

#include <iostream>
#include <string>
using namespace std::literals::string_literals;

#include <nlohmann/json.hpp>

namespace hd
{

// macros for conversion to json and iostream operators
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(js::dev_id, a_id, a_index, a_name, sys_name, sys_vendor_id, sys_product_id)
std::ostream& operator<<(std::ostream& os, const js::dev_id& dev);

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(js::dev_cap, axis_flags, axis_string, nAxis, nButton, nPOV)
std::ostream& operator<<(std::ostream& os, const js::dev_cap& c);

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(js::dev_button, index, name)
std::ostream& operator<<(std::ostream& os, const js::dev_button& b);

} // namespace hd

#endif // HD_DI8JOY_JSON_IO_HPP