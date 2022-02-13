# give our executable a name
set(EXEC_NAME condition_var)

# Manually add the sources
set(SOURCES src/condition_var.cpp)
# set(HEADERS "")

add_executable(${EXEC_NAME} ${SOURCES})
# add_executable(${EXEC_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_include_directories(${EXEC_NAME} PRIVATE /Users/daniel/prg/cpp/include)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)
