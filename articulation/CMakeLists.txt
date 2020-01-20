cmake_minimum_required(VERSION 3.15)
project(articulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(articulation main.cpp Graph.h Graph.cpp exceptions.h)