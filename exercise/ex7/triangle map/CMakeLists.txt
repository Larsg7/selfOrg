cmake_minimum_required(VERSION 3.5)
project(triangle_map)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(triangle_map ${SOURCE_FILES})