# give our executable a name
set(EXEC_NAME ode_int)

# Manually add the sources
set(SOURCES src/main.cpp src/derivatives.cpp src/grid.cpp src/output.cpp
            src/rk4.cpp)

add_executable(${EXEC_NAME} ${SOURCES})

# target link libraries have to be added AFTER add_executable or add_library!
target_include_directories(${EXEC_NAME}
                           PRIVATE ${CMAKE_SOURCE_DIR}/../../include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../include/mdspan/include)

target_compile_definitions(${EXEC_NAME} PUBLIC MDSPAN_USE_BRACKET_OPERATOR=1 MDSPAN_USE_PAREN_OPERATOR=0 MDSPAN_CXX_STANDARD=23)
                         
find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt-header-only)

find_package(
  VTK
  COMPONENTS vtkCommonColor vtkCommonCore vtkCommonDataModel vtkIOXML
  QUIET)
if(NOT VTK_FOUND)
  message("Skipping ${EXEC_NAME}: ${VTK_NOT_FOUND_MESSAGE}")
  return()
endif()
message(STATUS "VTK_VERSION: ${VTK_VERSION}")

target_link_libraries(${EXEC_NAME} PRIVATE ${VTK_LIBRARIES})
# vtk_module_autoinit is needed
vtk_module_autoinit(TARGETS ${EXEC_NAME} MODULES ${VTK_LIBRARIES})