# give our executable a name
set(EXEC_NAME json)

# Manually add the sources
set(SOURCES src/main.cpp)

add_executable(${EXEC_NAME} ${SOURCES})

# target_include_directories must be specified AFTER add_executable!
target_include_directories(${EXEC_NAME} PUBLIC include)

target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)

target_link_libraries(${EXEC_NAME} PRIVATE nlohmann_json::nlohmann_json)
