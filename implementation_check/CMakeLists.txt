# give our executable a name
set(EXEC_NAME implementation_check)

# Manually add the sources
set(SOURCES src/implementation_check.cpp)

add_executable(${EXEC_NAME} ${SOURCES})
