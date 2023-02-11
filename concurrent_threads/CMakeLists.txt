
set(EXEC_NAME concurrent_threads)

add_executable(${EXEC_NAME} src/main.cpp)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt-header-only)
