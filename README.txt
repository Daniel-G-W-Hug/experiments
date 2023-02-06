to configure and build with cmake:

- if it does not exist yet, create a build directory and change to it:

mkdir build
cd build

- install dependencies via vcpkg (vcpkg must be installed in ~/prg/cpp/vcpkg)
- the CMAKE_TOOLCHAIN_FILE is set in CMakeLists.txt accordingly:
if (WIN32)
  set(CMAKE_TOOLCHAIN_FILE "C:/Users/danie/prg/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake")
else
  set(CMAKE_TOOLCHAIN_FILE /Users/daniel/prg/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake)
endif()

vcpkg install fmt
vcpkg install boost-circular-buffer
vcpkg install stlab
vcpkg install mdspan
vcpkg install vtk
vcpkg install josuttis-jthread
vcpkg install nlohmann-json
vcpkg install proxy
vcpkg install tinyspline

- configure and build using cmake:

cmake .. -G "Visual Studio 17 2022" -T host=x64 -A x64
cmake --build .

or use ninja:

cmake .. -G "Ninja"
ninja

- to remove the build directory go to the project directory

rm -rf build/*

or

rmdir /S /Q build
