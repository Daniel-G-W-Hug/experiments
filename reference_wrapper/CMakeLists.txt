# give our executable a name
set(EXEC_NAME reference_wrapper)

# Manually add the sources
set(SOURCES src/main.cpp)
# set(HEADERS "")

# target_include_directories(${PROJECT_NAME} PRIVATE
# ${CMAKE_SOURCE_DIR}/include)

add_executable(${EXEC_NAME} ${SOURCES})
# add_executable(${EXEC_NAME} ${SOURCES} ${HEADERS})

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)
