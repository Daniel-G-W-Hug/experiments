# give our executable a name
set(EXEC_NAME circular_buffer)

# Manually add the sources
set(SOURCES src/main.cpp)
# set(HEADERS "")

add_executable(${EXEC_NAME} ${SOURCES})
# add_executable(${EXEC_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)

find_package(Boost REQUIRED)
target_include_directories(${EXEC_NAME} PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(${EXEC_NAME} PRIVATE Boost::boost)
