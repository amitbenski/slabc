cmake_minimum_required(VERSION 3.2)
project(MyString)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES MyString.c MyString.h MyStringMain.c)
add_executable(MyString ${SOURCE_FILES})