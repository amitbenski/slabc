cmake_minimum_required(VERSION 3.2)
project(nimgame)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES
    NimGame.c)

add_executable(nimgame ${SOURCE_FILES})