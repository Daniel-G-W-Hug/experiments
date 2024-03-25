#pragma once

#include <cassert>
#include <string>
#include <vector>

#include "lua.hpp"

#include "lua_type.hpp" // type definitions to cover lua value types

class lua_executor {
  public:

    lua_executor();
    virtual ~lua_executor(); // virtual, thus can be used as base class later

    bool execute_file(std::string const& path) const;
    bool execute(std::string const& script) const;

    void set_global(std::string const& name, lua_value const& value) const;
    lua_value get_global(std::string const& name) const;

    void set_table(std::string const& table, std::string const& key,
                   lua_value const& value) const;
    lua_value get_table(std::string const& table, std::string const& key) const;

    void set_table(std::string const& table, int index, lua_value const& value) const;
    lua_value get_table(std::string const& table, int index) const;

    template <typename... Ts>
    lua_value call(const std::string& function, const Ts&... parameters) const;

    template <typename... Ts>
    std::vector<lua_value> vcall(const std::string& function,
                                 const Ts&... parameters) const;

  private:

    bool pcall(int nargs = 0, int nresults = 0) const;

    void push_lua_value(const lua_value& value) const;

    lua_value get_lua_value(int index) const;

    lua_value pop_lua_value() const;
    std::vector<lua_value> pop_lua_values(int n) const;
    std::string pop_string() const;

    void dump_lua_stack() const;

    lua_State* const L;
};

template <typename... Ts>
lua_value lua_executor::call(const std::string& function, const Ts&... parameters) const
{
    // push function on stack
    int type = lua_getglobal(L, function.c_str());
    assert(type == LUA_TFUNCTION);

    // push args on stack
    for (const auto& p : std::initializer_list<lua_value>{parameters...}) {
        push_lua_value(p);
    }

    // call function and assume one return value
    if (pcall(sizeof...(parameters), 1)) {
        // send back the return value
        return pop_lua_value();
    }
    // otherwise return nil
    return lua_nil::make();
}

template <typename... Ts>
std::vector<lua_value> lua_executor::vcall(const std::string& function,
                                           const Ts&... parameters) const
{

    // get current stack size
    int stack_size = lua_gettop(L);

    // push function on stack
    int type = lua_getglobal(L, function.c_str());
    assert(type == LUA_TFUNCTION);

    // push args on stack
    for (const auto& p : std::initializer_list<lua_value>{parameters...}) {
        push_lua_value(p);
    }

    // call function and assume multiple return values
    if (pcall(sizeof...(parameters), LUA_MULTRET)) {
        int nresults = lua_gettop(L) - stack_size; // number of returned values
        return pop_lua_values(nresults);
    }

    // in case of error return empty vector
    return std::vector<lua_value>();
}