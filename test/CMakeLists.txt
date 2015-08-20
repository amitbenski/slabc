cmake_minimum_required(VERSION 3.2)
project(test)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES main.c)
add_executable(test ${SOURCE_FILES})