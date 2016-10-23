cmake_minimum_required(VERSION 3.5)
project(checked_numbers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp checked_numbers.h)
add_executable(checked_numbers ${SOURCE_FILES})