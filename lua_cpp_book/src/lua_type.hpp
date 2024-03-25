#pragma once

#include <cstddef>
#include <string>
#include <variant>

// implemented lua types
enum class lua_type { nil, boolean, number, string, function, table };

// nil
struct lua_nil final { // final = no further inheritance

    const enum lua_type type = lua_type::nil; // type indicator
    const std::nullptr_t value = nullptr;     // type value

    static lua_nil make()
    {
        // only the static function can return new objects
        return lua_nil();
    }

  private: // private constructor, no one can create, copy or move that value

    lua_nil() = default;
};

// boolean
struct lua_boolean final {

    const enum lua_type type = lua_type::boolean;
    const bool value;

    static lua_boolean make(const bool value) { return lua_boolean(value); }

  private:

    lua_boolean(const bool value) : value(value) {}
};

// number
struct lua_number final {

    const enum lua_type type = lua_type::number;
    const double value;

    static lua_number make(const double value) { return lua_number(value); }

  private:

    lua_number(const double value) : value(value) {}
};

// string
struct lua_string final {

    const enum lua_type type = lua_type::string;
    const std::string value;

    static lua_string make(const std::string& value) { return lua_string(value); }

  private:

    lua_string(const std::string& value) : value(value) {}
};

// function
struct lua_function final {

    const enum lua_type type = lua_type::function;
    const std::nullptr_t value = nullptr; // type value

    static lua_function make() { return lua_function(); }

  private:

    lua_function() = default;
};

// table
struct lua_table final {

    const enum lua_type type = lua_type::table;
    const std::nullptr_t value = nullptr; // type value

    static lua_table make() { return lua_table(); }

  private:

    lua_table() = default;
};

// lua_value is a variant including all defined lua value types
using lua_value =
    std::variant<lua_nil, lua_boolean, lua_number, lua_string, lua_function, lua_table>;

// defining access to the type field of a lua_value
//
// (must be inline due to definition in header, would otherwise create linker error when
// included in several files)
inline enum lua_type get_lua_type(const lua_value& value)
{
    return std::visit([](const auto& v) { return v.type; }, value);
}

// defining access to the value field of a lua_value represented as a string
//
inline std::string get_lua_value_string(const lua_value& value)
{

    switch (get_lua_type(value)) {
        case lua_type::nil:
            return "nil";
        case lua_type::boolean:
            return std::get<lua_boolean>(value).value ? "true" : "false";
        case lua_type::number:
            return std::to_string(std::get<lua_number>(value).value);
        case lua_type::string:
            return std::get<lua_string>(value).value;
        case lua_type::function:
            return "function";
        case lua_type::table:
            return "table";
    }
}