cmake_minimum_required(VERSION 3.26)
project(untitled1 C)

set(CMAKE_C_STANDARD 11)

add_library(untitled1 library.c)

add_subdirectory(algorithms)
add_subdirectory(data_structures)
