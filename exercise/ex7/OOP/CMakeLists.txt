cmake_minimum_required(VERSION 3.5)
project(OOP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(OOP ${SOURCE_FILES})