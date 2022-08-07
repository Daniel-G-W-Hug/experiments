# give our executable a name
set(EXEC_NAME mdspan_test)

# Manually add the sources
set(SOURCES src/main.cpp)
# set(HEADERS "")

add_executable(${EXEC_NAME} ${SOURCES})

# include path to find "single-header" branch of mdspan
#target_include_directories(${EXEC_NAME} PUBLIC /Users/daniel/prg/cpp/include)
target_include_directories(${EXEC_NAME} PUBLIC C:/Users/danie/prg/cpp/include)

target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)

#target_link_libraries(${EXEC_NAME} PRIVATE mdspan)

