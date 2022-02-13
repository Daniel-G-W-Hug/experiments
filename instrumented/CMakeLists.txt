# give our executable a name
set(EXEC_NAME instrumented)

# Manually add the sources
set(SOURCES src/main.cpp src/instrumented.cpp)
# set(HEADERS "")

add_executable(${EXEC_NAME} ${SOURCES})
# add_executable(${EXEC_NAME} ${SOURCES} ${HEADERS})

# target_include_directories must be specified AFTER add_executable!
target_include_directories(${EXEC_NAME} PUBLIC include)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)
