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

cmake_minimum_required(VERSION 3.23)

# to use gcc-11 and g++-11 instead of default c / c++ (must come before project
# line)
#[[
set(CMAKE_C_COMPILER "gcc-11")
set(CMAKE_CXX_COMPILER "g++-11")
# ]]
# specific for MacOS
#[[
set(CMAKE_XCODE_ATTRIBUTE_CC "gcc-11")
set(CMAKE_XCODE_ATTRIBUTE_CXX "g++-11")
# ]]

set(CMAKE_C_COMPILER "gcc-11")
set(CMAKE_CXX_COMPILER "g++-11")

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
# either manually or via CMake Tools configure args, e.g.
# '-DCMAKE_TOOLCHAIN_FILE=/Users/daniel/prg/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake'
# if(NOT DEFINED CMAKE_TOOLCHAIN_FILE) message( FATAL_ERROR
# "CMAKE_TOOLCHAIN_FILE must be defined to use vcpkg. Configuration aborted." )
# endif()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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
add_subdirectory(fmt)
add_subdirectory(circular_buffer)
add_subdirectory(implementation_check)
add_subdirectory(instrumented)
add_subdirectory(raii)
add_subdirectory(reference_wrapper)
add_subdirectory(forest)

# "filter_transform" currently does not work in clang++, but on MACOS on g++
# only (ranges not implemented for clang++ in c++20)

# add_subdirectory(filter-transform)

# "mdspan" works on MACOS in clang++, but not in g++-11 (terminates with error)

# add_subdirectory(mdspan)

# "condition_var" does work in clang++ only with local jthread instance; does
# not link with g++ (linker error)

# add_subdirectory(condition_var)

# "type_erasure" works on clang++, but not on g++-11 on MACOS (Linker error)

# add_subdirectory(type_erasure)

# "vtk" works on clang++, but not on g++-11 on MACOS (Linker error)

# add_subdirectory(vtk)
