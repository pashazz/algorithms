cmake_minimum_required(VERSION 3.15)
project(binarytree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fsanitize=address,undefined -fno-sanitize-recover=all -std=c++17 -O2 -Wall -Werror -Wsign-compare")

add_executable(heap main.cpp bintree.h Heap.cpp Heap.h)