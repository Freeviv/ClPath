cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 17)

project(cl_path)

set(OPENCL_FILES
    mmul.cl
    kernel.cl
)

set(SRCS
    main.cpp
    cpu_algorithm.cpp
    gpu_algorithm.cpp
)

set(HDRS
    datatypes.h
    utils.h
    cpu_algorithm.hpp
    gpu_algorithm.hpp
)

set(VIS_SRCS
    visualization.cpp
    visualization.hpp
    configuration.hpp
)

add_subdirectory(external)
add_library(visualization ${VIS_SRCS})
target_link_libraries(visualization png lodepng)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS} ${OPENCL_FILES})
target_link_libraries(${PROJECT_NAME} OpenCL visualization)
