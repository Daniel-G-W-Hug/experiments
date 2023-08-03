# give our executable a name
set(EXEC_NAME json_io)

# Manually add the sources
set(HEADERS include/di8joy.hpp include/di8joy_json_io.hpp)
set(SOURCES src/main.cpp src/di8joy_json_io.cpp)

add_executable(${EXEC_NAME} ${HEADERS} ${SOURCES})

# target link libraries have to be added AFTER add_executable or add_library!
target_include_directories(${EXEC_NAME} PRIVATE include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${EXEC_NAME}
                           PRIVATE ${CMAKE_SOURCE_DIR}/../../include)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt-header-only)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE nlohmann_json::nlohmann_json)

# The package nlohmann-json can be configured to not provide implicit conversions via a custom triplet file:
#     set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)
# For more information, see the docs here:
#     https://json.nlohmann.me/api/macros/json_use_implicit_conversions/