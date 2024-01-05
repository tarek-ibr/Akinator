cmake_minimum_required(VERSION 3.26)
project(project C)

set(CMAKE_C_STANDARD 11)

add_executable(project main.c
        cmake-build-debug/test.cpp
        learn.h
        play.h
)
