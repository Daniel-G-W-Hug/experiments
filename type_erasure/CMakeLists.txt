# give our executable a name
set(EXEC_NAME type_erasure)

# Manually add the sources
set(SOURCES src/main.cpp)

add_executable(${EXEC_NAME} ${SOURCES})

target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)
