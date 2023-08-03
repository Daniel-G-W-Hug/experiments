# give our executable a name
set(EXEC_NAME implementation_check)

# Manually add the sources
set(SOURCES src/implementation_check.cpp)

add_executable(${EXEC_NAME} ${SOURCES})
add_executable(print_char_table src/print_char_table.cpp)

# target link libraries have to be added AFTER add_executable or add_library!
target_include_directories(${EXEC_NAME} PRIVATE include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../include)
