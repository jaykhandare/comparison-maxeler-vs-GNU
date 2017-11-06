cmake_minimum_required(VERSION 3.8)
project(comparison_maxeler_vs_GNU)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.c)

add_executable(comparison_maxeler_vs_GNU ${SOURCE_FILES})