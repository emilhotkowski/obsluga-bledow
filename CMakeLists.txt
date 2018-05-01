# cmake_minimum_required(VERSION <specify CMake version here>)
project(obsluga_bledow)

set(CMAKE_CXX_STANDARD 11)

add_executable(obsluga_bledow
        klientTCP.c
        LICENSE
        serwerTCP.cpp)
