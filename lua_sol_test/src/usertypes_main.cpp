#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

#include "usertypes.hpp"

#include <iostream> // cout, cerr
#include <vector>


// int main(int argc, char* argv[])
int main()
{

    try {
        sol::state lua;
        lua.open_libraries();

        // // define usertypes before using them
        // sol::usertype<vec2d> vec2d_t = lua.new_usertype<vec2d>(
        //     "vec2d", sol::constructors<vec2d(), vec2d(int, int)>());

        // vec2d_t["print"] = &vec2d::print;
        // vec2d_t["x"] = &vec2d::x;
        // vec2d_t["y"] = &vec2d::y;

        // define usertypes before using them
        sol::usertype<vec2d<double>> vec2d_t = lua.new_usertype<vec2d<double>>(
            "vec2d",
            sol::constructors<vec2d<double>(), vec2d<double>(double, double),
                              vec2d<double>(vec2d<double>)>(),
            // "x", &vec2d<double>::x, "y", &vec2d<double>::y,
            sol::meta_function::unary_minus,
            sol::resolve<vec2d<double>(vec2d<double> const&)>(::operator-),
            sol::meta_function::addition,
            sol::resolve<vec2d<double>(vec2d<double> const&, vec2d<double> const&)>(
                ::operator+),
            sol::meta_function::subtraction,
            sol::resolve<vec2d<double>(vec2d<double> const&, vec2d<double> const&)>(
                ::operator-),
            sol::meta_function::multiplication,
            sol::overload(
                sol::resolve<vec2d<double>(vec2d<double> const&, double)>(::operator*),
                sol::resolve<vec2d<double>(double, vec2d<double> const&)>(::operator*),
                // operator* must be assigned to type with first complex arg
                sol::resolve<vec2d<double>(vec2d<double> const&,
                                           mvec2d_e<double> const&)>(::operator*),
                sol::resolve<mvec2d_e<double>(vec2d<double> const&,
                                              vec2d<double> const&)>(::operator*)));

        // alternative to declaration above (see comment after constructors)
        vec2d_t["x"] = &vec2d<double>::x;
        vec2d_t["y"] = &vec2d<double>::y;

        lua.new_usertype<mvec2d_e<double>>(
            "mvec2d_e",
            sol::constructors<mvec2d_e<double>(), mvec2d_e<double>(double, double),
                              mvec2d_e<double>(mvec2d_e<double>)>(),
            "c0", &mvec2d_e<double>::c0, "c1", &mvec2d_e<double>::c1,
            sol::meta_function::unary_minus,
            sol::resolve<mvec2d_e<double>(mvec2d_e<double> const&)>(::operator-),
            sol::meta_function::addition,
            sol::resolve<mvec2d_e<double>(mvec2d_e<double> const&,
                                          mvec2d_e<double> const&)>(::operator+),
            sol::meta_function::subtraction,
            sol::resolve<mvec2d_e<double>(mvec2d_e<double> const&,
                                          mvec2d_e<double> const&)>(::operator-),
            sol::meta_function::multiplication,
            sol::overload(
                sol::resolve<mvec2d_e<double>(mvec2d_e<double> const&, double)>(
                    ::operator*),
                sol::resolve<mvec2d_e<double>(double, mvec2d_e<double> const&)>(
                    ::operator*),
                // operator* must be assigned to type with first complex arg
                sol::resolve<vec2d<double>(mvec2d_e<double> const&,
                                           vec2d<double> const&)>(::operator*),
                sol::resolve<mvec2d_e<double>(mvec2d_e<double> const&,
                                              mvec2d_e<double> const&)>(::operator*)));

        // make defined constants available as global variables
        lua["e1_2d"] = &e1_2d;
        lua["e2_2d"] = &e2_2d;

        // run the lua script
        lua.safe_script_file("../../lua_sol_test/input/usertypes.lua");

        // using namespace hd;
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