cmake_minimum_required(VERSION 3.15)
project(calculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(calculator main.cpp ParserException.h Operator.h Operators.h)