# give our executable a name
set(EXEC_NAME fmt)

# Manually add the sources
set(SOURCES src/main.cpp)

add_executable(${EXEC_NAME} ${SOURCES})
# add_executable(${EXEC_NAME} ${SOURCES} ${HEADERS})

# target_include_directories(${EXEC_NAME} PRIVATE
# /Users/daniel/prg/cpp/include/fmt/include)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)
