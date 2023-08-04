#[[ directory structure:
#
# .
# ├── CMakeLists.txt
# ├── build
# ├── subdir1  // all that is required for subproject1
# │   ├── CMakeLists.txt
# │   ├── include
# │   │   └── *.hpp
# │   └── src
# │       └── *.cpp
# ├── subdir2  // all that is required for subproject1
# │   ├── CMakeLists.txt
# │   ├── include
# │   │   └── *.hpp
# │   └── src
# │       └── *.cpp
# └── ...
#
##################################################################
# usage: execute "cmake .. && make" from build directory
#    or: execute "cmake .. -G"Ninja" && ninja from build directory
#
# alternative to build:  "cmake --build ." from build directory
##################################################################
#]]
#[[ hint: backet comment will not be formated by cmake-format]]

cmake_minimum_required(VERSION 3.25)

# to use gcc-13 and g++-13 instead of default c / c++ (must come before project
# line [[
# set(CMAKE_C_COMPILER "gcc-13")
# set(CMAKE_CXX_COMPILER "g++-13")
# ]]

# CMAKE_TOOLCHAIN_FILE must be defined BEFORE project(...)!
if(WIN32)
  set(CMAKE_TOOLCHAIN_FILE "C:/Users/danie/prg/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake")
else()
  set(CMAKE_TOOLCHAIN_FILE "/Users/daniel/prg/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

#
# for trial of new features, libs or system values"
#
project(
  experiments
  VERSION 0.1
  LANGUAGES CXX)

# set(CMAKE_VERBOSE_MAKEFILE ON)  // alternative: make VERBOSE=1
# add_definitions(-Dxxx)

# make sure cmake is called with indication of CMAKE_TOOLCHAIN_FILE (vcpkg)
# e.g. via .zshrc export CMAKE_TOOLCHAIN_FILE="/Users/daniel/prg/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake"
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  message(FATAL_ERROR
          "CMAKE_TOOLCHAIN_FILE must be defined to use vcpkg. Configuration aborted.")
endif()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# set a default build type: Debug | RelWithDebInfo | Release | MinSizeRel
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
  message(STATUS "Build type not specified: use Debug mode by default.")
endif()

if(CMAKE_BUILD_TYPE EQUAL "Debug")
  if(MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
  else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
  endif()
endif()

# incrementally add all subdirectories needed; examples work on all complilers
add_subdirectory(hello)
add_subdirectory(fmt_test)                # dep: fmt
add_subdirectory(circular_buffer)         # dep: fmt, boost-circular-buffer
add_subdirectory(implementation_check)
add_subdirectory(instrumented)            # dep: fmt
add_subdirectory(raii)                    # dep: fmt
add_subdirectory(filter-transform)

# "mdspan" works on MACOS in clang++, but not in g++-12 (terminates with error)
add_subdirectory(mdspan_test)             # dep: fmt, mdspan

# "ode_int" as another application of mdspan (dependency vtk)
add_subdirectory(ode_int)                 # dep: fmt, vtk

# "condition_var" does work in clang++ only with local jthread instance
add_subdirectory(condition_var)           # dep: fmt, josuttis-jthread

# "type_erasure" works on clang++, but not on g++-12 on MACOS (Linker error)
add_subdirectory(type_erasure)            # dep: fmt

# "vtk" works on clang++, but not on g++-11 on MACOS (Linker error)
add_subdirectory(vtk)                     # dep: fmt, vtk

# test json library from nlohmann
add_subdirectory(json_test)               # dep: fmt, nlohmann-json

# example using json library from nlohmann (button mapping)
add_subdirectory(json_io)                 # dep: fmt, nlohmann-json

# proxy library for unintrusive polymorphism
add_subdirectory(proxy)                   # dep: fmt, nlohmann-json, proxy

# error handling tests
# <source_location> does currently not yet work with clang++ (header not found as of 01/2023)
# add_subdirectory(error_handling)

# tinyspline trial
add_subdirectory(tinyspline)               # dep: fmt, tinyspline

add_subdirectory(ctor_dtor)
