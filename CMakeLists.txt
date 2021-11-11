cmake_minimum_required(VERSION 3.20)
project(colorize)

set(CMAKE_CXX_STANDARD 23)

add_executable(colorize main.cpp src/index_of.cpp src/merge.cpp src/join.cpp src/str_convert.cpp)
