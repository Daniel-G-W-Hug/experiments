#include "lua_executor.hpp"

#include "fmt/format.h"

int main()
{
    lua_executor lua;
    lua.execute_file("../../lua_cpp_book/src/executor.lua"); // exec lua from file

    // lua.execute("print('Hello Lua!')"); // exec lua from string

    // lua.execute(
    //     "hello()"); // exec lua function read from script (in execution context lua)

    // lua.set_global("whom", lua_string::make("Lua"));
    // lua.execute("hello()");

    // lua.execute("print(greetings('Lua'))"); // exec lua from string calling a lua
    // function

    // // calling lua function from C++ with argument
    // fmt::println(
    //     "{}", get_lua_value_string(lua.call("greetings", lua_string::make("lua
    //     world!"),
    //                                         lua_number::make(3.14))));

    // calling lua function from C++ with multiple arguments and multiple return values
    //
    // fmt::print("\n");
    // auto results = lua.vcall("dump_params", lua_string::make("hello"),
    //                          lua_number::make(3.14), lua_boolean::make(true),
    //                          lua_nil::make(), lua_string::make("not_shown"));
    // for (const auto& r : results) {
    //     fmt::println("{}", get_lua_value_string(r));
    // }

    // // calling lua function from C++ with multiple arguments and multiple return values
    // fmt::print("\n");
    // results = lua.vcall("dump_params", lua_string::make("hello"),
    // lua_number::make(3.14),
    //                     lua_boolean::make(true), lua_string::make("shown"));
    // for (const auto& r : results) {
    //     fmt::println("{}", get_lua_value_string(r));
    // }


    fmt::println("pos['x'] = {}", std::get<lua_number>(lua.get_table("pos", "x")).value);
    fmt::println("pos['y'] = {}", std::get<lua_number>(lua.get_table("pos", "y")).value);

    lua.set_table("pos", "x", lua_number::make(-2));
    lua.set_table("pos", "y", lua_number::make(-4));

    fmt::println("pos['x'] = {}", std::get<lua_number>(lua.get_table("pos", "x")).value);
    fmt::println("pos['y'] = {}", std::get<lua_number>(lua.get_table("pos", "y")).value);

    lua.set_table("pos", 1, lua_number::make(-12));
    lua.set_table("pos", 2, lua_number::make(-24));

    fmt::println("pos[1] = {}", std::get<lua_number>(lua.get_table("pos", 1)).value);
    fmt::println("pos[1] = {}", std::get<lua_number>(lua.get_table("pos", 2)).value);

    lua.execute("pr.dump(pos)");

    fmt::println("seq[1] = {}", std::get<lua_number>(lua.get_table("seq", 1)).value);
    fmt::println("seq[2] = {}", std::get<lua_number>(lua.get_table("seq", 2)).value);
    fmt::println("seq[3] = {}", std::get<lua_number>(lua.get_table("seq", 3)).value);

    lua.set_table("seq", 1, lua_number::make(-1));
    lua.set_table("seq", 2, lua_number::make(-4));
    lua.set_table("seq", 3, lua_number::make(-7));

    fmt::println("seq[1] = {}", std::get<lua_number>(lua.get_table("seq", 1)).value);
    fmt::println("seq[2] = {}", std::get<lua_number>(lua.get_table("seq", 2)).value);
    fmt::println("seq[3] = {}", std::get<lua_number>(lua.get_table("seq", 3)).value);

    return 0;
}