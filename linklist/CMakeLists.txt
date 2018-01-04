cmake_minimum_required(VERSION 3.8)
project(linklist)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp linklist.cpp linklist.h)
add_executable(linklist ${SOURCE_FILES})