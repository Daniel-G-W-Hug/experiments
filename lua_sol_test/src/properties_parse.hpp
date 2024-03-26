#pragma once

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include "fmt/format.h"
#include "fmt/ranges.h"

#include "properties.hpp"

#include <vector>

namespace hd {

window parse_window(sol::state& lua);
font parse_font(sol::state& lua);

circle parse_circle(sol::state& lua);
std::vector<circle> parse_circle_seq(sol::state& lua);

rectangle parse_rectangle(sol::state& lua);
std::vector<rectangle> parse_rectangle_seq(sol::state& lua);

} // namespace hd