# give our executable a name
set(EXEC_NAME module_test)

# Manually add the sources
set(SOURCES src/main.cpp)

add_executable(${EXEC_NAME} ${SOURCES})

# target link libraries have to be added AFTER add_executable or add_library!
# target_include_directories(${EXEC_NAME} PRIVATE include)
# target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${EXEC_NAME}
                          PRIVATE ${CMAKE_SOURCE_DIR}/../../include)
