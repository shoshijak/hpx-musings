# note for Shoshana: build with
# cmake -DHPX_WITH_MALLOC=jemalloc -DHPX_DIR=~/Documents/CSCS/hpx-build/lib/cmake/HPX

cmake_minimum_required(VERSION 2.8)

project(Turtles-all-the-way-down)

set(CXX g++ -5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(HPX)

add_hpx_executable(turtle-main
  ESSENTIAL
  SOURCES turtle-main.cpp
  COMPONENT_DEPENDENCIES iostreams
)
