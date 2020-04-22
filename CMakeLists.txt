cmake_minimum_required(VERSION 3.15)
project(CSV_Reader)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(CSV_Reader main.cpp)