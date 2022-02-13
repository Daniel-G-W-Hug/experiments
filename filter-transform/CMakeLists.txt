# give our executable a name
set(EXEC_NAME filter-transform)

# Manually add the sources
set(SOURCES src/filter-transform.cpp)
# set(HEADERS "")

add_executable(${EXEC_NAME} ${SOURCES})
# add_executable(${EXEC_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)

find_package(range-v3 CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE range-v3 range-v3-meta
                                           range-v3::meta range-v3-concepts)
