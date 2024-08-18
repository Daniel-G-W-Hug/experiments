# give our executable a name
set(EXEC_NAME circular_buffer)

# Manually add the sources
set(SOURCES src/main.cpp)
# set(HEADERS "")

add_executable(${EXEC_NAME} ${SOURCES})

# target link libraries have to be added AFTER add_executable or add_library!
target_include_directories(${EXEC_NAME} PRIVATE include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../include)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt-header-only)

find_package(Boost CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE Boost::boost)
