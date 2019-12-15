cmake_minimum_required(VERSION 3.15)
project(sort)

set(CMAKE_CXX_STANDARD 17)

add_executable(merge utils.h merge_main.cpp mergesort.cpp mergesort.h)
add_executable(merge_binsearch utils.h mergesort.cpp mergesort.h  MergeSortBinarySearch.cpp MergeSortBinarySearch.h merge_binsearch_main.cpp)