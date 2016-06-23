cmake_minimum_required(VERSION 3.5)
project(neuralNetwork)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -llapack -lblas")

set(SOURCE_FILES class.neuralNetwork.cpp)
add_executable(neuralNetwork ${SOURCE_FILES})