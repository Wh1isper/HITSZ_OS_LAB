cmake_minimum_required(VERSION 3.10)
project(os_lab2_doc)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_CXX_STANDARD 14)
aux_source_directory(. DIR_SRCS)
add_executable(os_lab2_doc ${DIR_SRCS})