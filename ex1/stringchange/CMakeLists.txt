cmake_minimum_required(VERSION 3.2)
project(stringchange)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES
    StringChange.c)

add_executable(stringchange ${SOURCE_FILES})