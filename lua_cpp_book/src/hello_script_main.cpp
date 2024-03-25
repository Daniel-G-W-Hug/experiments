#include "fmt/format.h"

#include "lua.hpp"

int main()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_loadfile(L, "../../lua_cpp_book/src/script.lua") || lua_pcall(L, 0, 0, 0)) {
        fmt::println("Error: {}", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    lua_close(L);
    return 0;
}