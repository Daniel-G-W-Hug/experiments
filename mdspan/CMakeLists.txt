# give our executable a name
set(EXEC_NAME mdspan)

# Manually add the sources
set(SOURCES src/main.cpp)
# set(HEADERS "")

add_executable(${EXEC_NAME} ${SOURCES})
# add_executable(${EXEC_NAME} ${SOURCES} ${HEADERS})

# include path to find "single-header" branch of mdspan
target_include_directories(${EXEC_NAME} PUBLIC /Users/daniel/prg/cpp/include)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)

# find_package(mdspan REQUIRED)
