# give our executable a name
set(EXEC_NAME condition_var)

# Manually add the sources
set(SOURCES src/condition_var.cpp)
# set(HEADERS "")

add_executable(${EXEC_NAME} ${SOURCES})
# add_executable(${EXEC_NAME} ${SOURCES} ${HEADERS})

# target link libraries have to be added AFTER add_executable or add_library!
target_include_directories(${EXEC_NAME} PRIVATE include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../include)

#target_include_directories(${EXEC_NAME} PRIVATE /Users/daniel/prg/cpp/include)
#target_include_directories(${EXEC_NAME} PUBLIC C:/Users/danie/prg/cpp/include)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt-header-only)

find_path(JOSUTTIS_JTHREAD_INCLUDE_DIRS "condition_variable_any2.hpp")
target_include_directories(${EXEC_NAME} PRIVATE ${JOSUTTIS_JTHREAD_INCLUDE_DIRS})
