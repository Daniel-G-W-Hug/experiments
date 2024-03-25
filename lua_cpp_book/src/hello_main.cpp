#include "fmt/format.h"

#include "lua.hpp"

int main()
{
    lua_State* L = luaL_newstate();
    fmt::println("Lua hello: Lua version number is {}", lua_version(L));
    lua_close(L);
    return 0;
}