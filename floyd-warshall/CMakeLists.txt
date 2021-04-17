Cmake_minimum_required(version 3.15)
project(floyd-warshall)

set(cmake_cxx_standard 14)

add_executable(fwarshall main.cpp graph.cpp graph.h edge.cpp edge.h constants.h)