# give our executable a name
set(EXEC_NAME ctor_dtor)

# Manually add the sources
set(SOURCES src/ctor_dtor_main.cpp)
set(SOURCES2 src/ctor_main.cpp)

add_executable(${EXEC_NAME} ${SOURCES})
add_executable(ctor ${SOURCES2})