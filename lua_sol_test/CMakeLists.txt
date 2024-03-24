# give our executable a name
set(EXEC_NAME lua_sol_test)

# Manually add the sources
set(SOURCES src/main.cpp)

add_executable(${EXEC_NAME} ${SOURCES})

# target link libraries have to be added AFTER add_executable or add_library!
target_include_directories(${EXEC_NAME} PRIVATE include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../include/sol2/include)

find_package(fmt CONFIG REQUIRED)
find_package(Lua 5.4 REQUIRED)

target_include_directories(${EXEC_NAME} PRIVATE ${LUA_INCLUDE_DIR})

target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt-header-only ${LUA_LIBRARIES})