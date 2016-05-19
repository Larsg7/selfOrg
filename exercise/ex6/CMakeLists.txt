cmake_minimum_required(VERSION 3.5)
project(ex6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    template.cpp)

add_executable(ex6 ${SOURCE_FILES})