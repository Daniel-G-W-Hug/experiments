#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

#include "properties.hpp"
#include "properties_parse.hpp"

#include <ostream>
#include <vector>


int main(int argc, char* argv[])
{

    sol::state lua;
    lua.open_libraries();
    lua.script_file("../../lua_sol_test/input/properties.lua");

    using namespace hd;

    window w = parse_window(lua);
    font f = parse_font(lua);
    std::vector<circle> cs = parse_circle_seq(lua);
    std::vector<rectangle> rs = parse_rectangle_seq(lua);

    std::cout << "\n";
    std::cout << "window = " << w << "\n\n";
    std::cout << "font = " << f << "\n\n";

    for (size_t i = 0; i < cs.size(); ++i) {
        std::cout << "circle[" << i << "] = \n" << cs[i] << "\n\n";
    }
    for (size_t i = 0; i < rs.size(); ++i) {
        std::cout << "rectangle[" << i << "] = \n" << rs[i] << "\n\n";
    }

    return 0;
}