# give our executable a name
set(EXEC_NAME reference_wrapper)

# Manually add the sources
set(SOURCES src/main.cpp)

# target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_executable(${EXEC_NAME} ${SOURCES})

target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)
