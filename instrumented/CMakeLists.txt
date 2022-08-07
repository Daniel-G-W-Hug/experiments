# give our executable a name
set(EXEC_NAME instrumented)

# Manually add the sources
set(SOURCES src/main.cpp src/instrumented.cpp)
# set(HEADERS "")

add_executable(${EXEC_NAME} ${SOURCES})

# target_include_directories must be specified AFTER add_executable!
target_include_directories(${EXEC_NAME} PUBLIC include)

target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)
