cmake_minimum_required(VERSION 3.15)
project(lis_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(lis_cpp main.cpp dynamic.h sequence.h)

add_executable(lis_val dynamic.h sequence.h some.cpp)