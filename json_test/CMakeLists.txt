# give our executable a name
set(EXEC_NAME json_test)

# Manually add the sources
set(HEADERS include/properties.hpp)
set(SOURCES src/main.cpp src/properties.cpp)

add_executable(${EXEC_NAME} ${HEADERS} ${SOURCES})

# target link libraries have to be added AFTER add_executable or add_library!
target_include_directories(${EXEC_NAME} PRIVATE include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${EXEC_NAME}
                           PRIVATE ${CMAKE_SOURCE_DIR}/../../include)

target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt-header-only)

target_link_libraries(${EXEC_NAME} PRIVATE nlohmann_json::nlohmann_json)
