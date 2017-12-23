cmake_minimum_required(VERSION 3.8)
project(LinkBinaryTree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp binarytree.h binarytree.cpp Queue.h Queue.cpp)
add_executable(LinkBinaryTree ${SOURCE_FILES} binarytree.h binarytree.cpp)