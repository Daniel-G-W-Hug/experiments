# give our executable a name
set(EXEC_NAME proxy)

# Manually add the sources
set(SOURCES src/main.cpp)

add_executable(${EXEC_NAME} ${SOURCES})

# target_include_directories must be specified AFTER add_executable!
target_include_directories(${EXEC_NAME} PUBLIC include)
target_include_directories(${EXEC_NAME} PUBLIC /Users/daniel/prg/cpp/include)
target_include_directories(${EXEC_NAME} PUBLIC C:/Users/danie/prg/cpp/include)

target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)

