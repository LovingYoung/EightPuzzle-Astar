cmake_minimum_required(VERSION 3.3)
project(Astar)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Location.h main.cpp)
add_executable(Astar ${SOURCE_FILES})