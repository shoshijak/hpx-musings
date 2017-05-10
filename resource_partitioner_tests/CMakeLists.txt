cmake_minimum_required(VERSION 2.8)

project(RP CXX)

set(CXX g++ -5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

find_package(HPX)



add_hpx_executable(RP-main
        ESSENTIAL
        SOURCES main.cpp ~/Documents/CSCS/hpx/src/runtime/resource_partitioner.cpp ~/Documents/CSCS/hpx/src/runtime/threads/policies/affinity_data.cpp
        HEADERS
        COMPONENT_DEPENDENCIES iostreams)

add_hpx_executable(RP-main-default
        ESSENTIAL
        SOURCES main_simple_default.cpp ~/Documents/CSCS/hpx/src/runtime/resource_partitioner.cpp ~/Documents/CSCS/hpx/src/runtime/threads/policies/affinity_data.cpp
        HEADERS
        COMPONENT_DEPENDENCIES iostreams)