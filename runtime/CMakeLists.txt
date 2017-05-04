
cmake_minimum_required(VERSION 2.8)

project(ExploreRuntime CXX)

set(CXX g++ -5)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

find_package(HPX)

add_hpx_executable(explore_runtime
        ESSENTIAL
        SOURCES main.cpp
        HEADERS
        COMPONENT_DEPENDENCIES iostreams
)