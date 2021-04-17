cmake_minimum_required(VERSION 3.15)
project(maze)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS  "-Wall")

add_executable(maze main.cpp maze.cpp maze.h WeighedGraph.h WeighedGraph.cpp)
add_executable(maze_test test.cpp maze.cpp maze.h WeighedGraph.h WeighedGraph.cpp catch.hh)