
cmake_minimum_required(VERSION 2.8)

project(RM_EXPERIMENT CXX)

set(CXX g++ -5)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

find_package(HPX)

add_hpx_executable(rm_experiment
        ESSENTIAL
        SOURCES main.cpp
        HEADERS test_functions.h system_characteristics.h resource_manager.h
        COMPONENT_DEPENDENCIES iostreams
)