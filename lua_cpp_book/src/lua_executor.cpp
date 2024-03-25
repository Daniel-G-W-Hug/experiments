#include "lua_executor.hpp"

#include <cassert>
#include <cstdio>
#include <initializer_list>

#include <fmt/format.h>

lua_executor::lua_executor() : L(luaL_newstate()) { luaL_openlibs(L); }

lua_executor::~lua_executor() { lua_close(L); }

bool lua_executor::execute_file(std::string const& path) const
{

    if (luaL_loadfile(L, path.c_str()) != LUA_OK) {
        fmt::println(stderr, "Failed to prepare file '{}': {}", path, pop_string());
        return false;
    }
    if (pcall()) {
        return true;
    }
    return false;
}

bool lua_executor::execute(std::string const& script) const
{

    if (luaL_loadstring(L, script.c_str()) != LUA_OK) {
        fmt::println(stderr, "Failed to prepare script: {}", pop_string());
        return false;
    }
    if (pcall()) {
        return true;
    }
    return false;
}

void lua_executor::set_global(std::string const& name, lua_value const& value) const
{
    push_lua_value(value);
    lua_setglobal(L, name.c_str());
}

lua_value lua_executor::get_global(std::string const& name) const
{
    lua_getglobal(L, name.c_str());
    return pop_lua_value();
}

void lua_executor::set_table(std::string const& table, std::string const& key,
                             lua_value const& value) const
{
    int type = lua_getglobal(L, table.c_str()); // push table onto stack
    assert(type == LUA_TTABLE);

    push_lua_value(value);
    lua_setfield(L, -2, key.c_str()); // -2 points to table
                                      // pushes the value on top of the stack to
                                      // the corresponding key in the table and
                                      // pops the value from the stack
    lua_pop(L, 1);                    // remove table from stack
}

lua_value lua_executor::get_table(std::string const& table, std::string const& key) const
{
    int type = lua_getglobal(L, table.c_str()); // push table onto stack
    assert(type == LUA_TTABLE);

    lua_getfield(L, -1, key.c_str()); // -1 points to table
                                      // pushes the value at the corresponding key
                                      // onto the stack
    lua_value value = pop_lua_value();
    lua_pop(L, 1); // remove table from stack
    return value;
}

void lua_executor::set_table(std::string const& table, int index,
                             lua_value const& value) const
{
    int type = lua_getglobal(L, table.c_str()); // push table onto stack
    assert(type == LUA_TTABLE);

    push_lua_value(value);
    lua_seti(L, -2, index); // -2 points to table
                            // set the value at the corresponding and
                            // pops the value from the stack
    lua_pop(L, 1);          // remove table from stack
}

lua_value lua_executor::get_table(std::string const& table, int index) const
{
    int type = lua_getglobal(L, table.c_str()); // push table onto stack
    assert(type == LUA_TTABLE);

    lua_geti(L, -1, index); // -1 points to table
                            // pushes the value at the corresponding
                            // table index onto the stack
    lua_value value = pop_lua_value();
    lua_pop(L, 1); // remove table from stack
    return value;
}

bool lua_executor::pcall(int nargs, int nresults) const
{
    if (lua_pcall(L, nargs, nresults, 0) != LUA_OK) {
        fmt::println(stderr, "Failed to execute Lua code: {}", pop_string());
        return false;
    }
    return true;
}

void lua_executor::push_lua_value(const lua_value& value) const
{
    switch (get_lua_type(value)) {
        case lua_type::nil:
            lua_pushnil(L);
            break;
        case lua_type::boolean:
            lua_pushboolean(L, std::get<lua_boolean>(value).value ? 1 : 0);
            break;
        case lua_type::number:
            lua_pushnumber(L, std::get<lua_number>(value).value);
            break;
        case lua_type::string:
            lua_pushstring(L, std::get<lua_string>(value).value.c_str());
            break;
        case lua_type::function:
            assert(false && "pushing a lua function is not yet supported");
            break;
        case lua_type::table:
            assert(false && "pushing a lua function is not yet supported");
            break;
    }
}

lua_value lua_executor::get_lua_value(int index) const
{
    switch (lua_type(L, index)) {
        case LUA_TNIL:
            return lua_nil::make();
        case LUA_TBOOLEAN:
            return lua_boolean::make(lua_toboolean(L, index) == 1);
        case LUA_TNUMBER:
            return lua_number::make((double)lua_tonumber(L, index));
        case LUA_TSTRING:
            return lua_string::make(lua_tostring(L, index));
        case LUA_TFUNCTION:
            return lua_function::make();
        case LUA_TTABLE:
            return lua_table::make();
        default:
            // for now for unsupported types
            return lua_nil::make();
    }
}

lua_value lua_executor::pop_lua_value() const
{
    lua_value value = get_lua_value(-1);
    lua_pop(L, 1);
    return value;
}

std::vector<lua_value> lua_executor::pop_lua_values(int n) const
{
    std::vector<lua_value> results;
    for (int i = n; i > 0; --i) {
        results.push_back(get_lua_value(-i));
    }
    lua_pop(L, n);

    return results;
}

std::string lua_executor::pop_string() const
{
    auto result = std::get<lua_string>(pop_lua_value());
    return result.value;
}

void lua_executor::dump_lua_stack() const
{
    fmt::println("The lua stack:");
    if (lua_gettop(L) == 0) {
        fmt::println("    Is currently empty.");
    }
    for (int i = lua_gettop(L); i >= 1; i--) {
        fmt::println("    {} [{}]", get_lua_value_string(get_lua_value(i)),
                     lua_typename(L, lua_type(L, i)));
    }
    fmt::println("\n");
}