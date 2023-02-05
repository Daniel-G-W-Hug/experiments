to configure and build with cmake:

- if it does not exist yet, create a build directory and change to it:

mkdir build
cd build

- install dependencies via vcpkg
- set environment: define CMAKE_TOOLCHAIN_FILE, e.g.
- export CMAKE_TOOLCHAIN_FILE="/Users/daniel/prg/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake"

vcpkg install fmt
vcpkg install boost-circular-buffer
vcpkg install stlab
vcpkg install mdspan
vcpkg install vtk
vcpkg install josuttis-jthread
vcpkg install nlohmann-json
vcpkg install proxy

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
