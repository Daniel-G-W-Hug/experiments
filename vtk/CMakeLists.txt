# give our executable a name
set(EXEC_NAME write_vtp)

# Manually add the sources
set(SOURCES src/write_vtp.cpp)
# set(HEADERS "")

add_executable(${EXEC_NAME} ${SOURCES})
# add_executable(${EXEC_NAME} ${SOURCES} ${HEADERS})

# target link libraries have to be added AFTER add_executable or add_library!
target_include_directories(${EXEC_NAME} PRIVATE include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../include)

target_link_libraries(${EXEC_NAME} PRIVATE fmt::fmt)

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
