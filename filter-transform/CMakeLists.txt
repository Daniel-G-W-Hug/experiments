# give our executable a name
set(EXEC_NAME filter-transform)

# Manually add the sources
set(SOURCES src/filter-transform.cpp)

add_executable(${EXEC_NAME} ${SOURCES})

target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)

