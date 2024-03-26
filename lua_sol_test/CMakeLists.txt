# give our executable a name
set(EXEC_NAME lua_sol_test)
set(EXEC_NAME2 properties_test)

# Manually add the sources
set(SOURCES src/simple_cfg_main.cpp)
set(SOURCES2 src/properties_main.cpp src/properties.cpp src/properties_parse.cpp)

add_executable(${EXEC_NAME} ${SOURCES})
add_executable(${EXEC_NAME2} ${SOURCES2})

# target link libraries have to be added AFTER add_executable or add_library!
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../include/sol2/include)

target_include_directories(${EXEC_NAME2} PRIVATE ${CMAKE_SOURCE_DIR}/../../include)
target_include_directories(${EXEC_NAME2} PRIVATE ${CMAKE_SOURCE_DIR}/../../include/sol2/include)

find_package(fmt CONFIG REQUIRED)
find_package(Lua 5.4 REQUIRED)

target_include_directories(${EXEC_NAME} PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt-header-only ${LUA_LIBRARIES})

target_include_directories(${EXEC_NAME2} PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(${EXEC_NAME2} PRIVATE fmt::fmt-header-only ${LUA_LIBRARIES})