#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

#include "properties.hpp"
#include "properties_parse.hpp"

#include <iostream> // cout, cerr
#include <vector>


// int main(int argc, char* argv[])
int main()
{

    try {
        sol::state lua;
        lua.open_libraries();
        lua.safe_script_file("../../lua_sol_test/input/properties.lua");

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
    }
    catch (sol::error const& e) {

        // some lua error occured
        std::cerr << e.what() << "\n";
        return -3;
    }
    catch (std::exception const& e) {
        // some non-lua error occured
        std::cerr << e.what() << "\n";
        return -2;
    }
    catch (...) {
        std::cerr << "ERROR: other, unexpected stuff happened.\n";
        return -1;
    }

    return 0;
}