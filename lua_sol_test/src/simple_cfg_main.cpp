#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <string>
#include <tuple>
#include <vector>

#include "fmt/format.h"
#include "fmt/ranges.h"

#include "hd/hd_keypress.hpp"


struct hw_config {
    std::string name;
    int width;
    int height;

    void print()
    {
        fmt::println("Name: {}\nWidth: {}\nHeight: {}\n", name, width, height);
    }
};


int main()
{

    sol::state lua;
    lua.open_libraries();

    // lua.script("print('bark bark bark!')", &sol::script_default_on_error);

    lua.script_file("../../lua_sol_test/input/simple_cfg.lua");

    hw_config screen;
    // screen.name = lua.get<std::string>("name");
    // screen.width = lua.get<int>("width");
    // screen.height = lua.get<int>("height");

    screen.name = lua["name"];
    screen.width = lua["width"];
    screen.height = lua["height"];

    fmt::println("==== screen after input from simple_lua.cfg ====");
    screen.print();

    bool isfullscreen = lua["config"]["fullscreen"];
    // sol::optional<bool> is_bool = lua["config"]["fullscreen"];
    // bool isfullscreen;
    // if (is_bool) {
    //     isfullscreen = is_bool.value();
    // }
    sol::table config = lua["config"];
    sol::table resolution = config.get<sol::table>("resolution");
    std::tuple<int, int> xyresolutiontuple = resolution.get<int, int>("x", "y");
    // alternative, step by step:
    // std::tuple<int, int> xyresolutiontuple;
    // std::get<0>(xyresolutiontuple) = resolution.get<int>("x");
    // std::get<1>(xyresolutiontuple) = resolution.get<int>("y");
    int x = lua["config"]["resolution"]["x"];
    int y = lua["config"]["resolution"]["y"];

    fmt::println("isfullscreen: {}", isfullscreen);
    fmt::println("xyresolutiontuple: {}", xyresolutiontuple);
    fmt::println("x = {}, y = {}", x, y);

    sol::table vec_table = lua["vec"];
    std::vector<int> v(vec_table.size());

    for (size_t i = 0; i < v.size(); ++i) {
        v[i] = lua["vec"][i + 1];
    }
    fmt::println("v: {}", fmt::join(v, ", "));

    for (size_t i = 0; i < v.size(); ++i) {
        lua["vec"][i + 1] = v[i] * 2;
    }

    lua.script("pr.dump(vec)");

    hd::cmdl_wait_for_enter();

    return 0;
}
