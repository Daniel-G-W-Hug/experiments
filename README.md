#experiments

For experiments to build, the hd repository needs to be available for inclusion via

target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../../include) 


## Dependencies:
    - hd header lib (separate install)
    - fmt (e.g. brew install fmt)
    - boost (e.g. brew install boost)
    - doctest (e.g. brew install doctest)
    - nlohmann-json (e.g. brew install nlohmann-json)
    - vtk (e.g. brew install vtk)
    - mdspan (e.g. from: https://github.com/kokkos/mdspan.git)
    - proxy (e.g. from: https://github.com/microsoft/proxy.git)
    - tinyspline (e.g. from: https://github.com/msteinbeck/tinyspline.git)
    - jthread (e.g. from: https://github.com/josuttis/jthread.git)

