# give our executable a name
set(EXEC_NAME forest)

# Manually add the sources
set(SOURCES src/forest.cpp)
# set(HEADERS "")

# target_include_directories(${PROJECT_NAME} PRIVATE
# ${CMAKE_SOURCE_DIR}/include)

add_executable(${EXEC_NAME} ${SOURCES})
# add_executable(${EXEC_NAME} ${SOURCES} ${HEADERS})

# add path to stlab
target_include_directories(${EXEC_NAME}
                           PUBLIC /Users/daniel/prg/cpp/lib/libraries)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)
