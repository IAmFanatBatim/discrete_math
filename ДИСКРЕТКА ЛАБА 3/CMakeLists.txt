cmake_minimum_required(VERSION 3.26)
project(_3 C)

set(CMAKE_C_STANDARD 11)

include_directories(ordered_array_set)

add_executable(_3
        ordered_array_set/ordered_array_set.c
        ordered_array_set/ordered_array_set.h
        main.c)
