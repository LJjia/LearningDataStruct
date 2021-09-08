cmake_minimum_required(VERSION 3.13)
project(Tree)

set(CMAKE_CXX_STANDARD 14)
aux_source_directory(${PROJECT_SOURCE_DIR}/ SRC_LIST_C)
include_directories(${PROJECT_SOURCE_DIR}/)

# 但是需要注意,如果是用的是C语言编译器,则可能会没有c++编译器的特性,因此会报warning
set(CMAKE_CXX_FLAGS "-Wno-writable-strings ${CMAKE_CXX_FLAGS}")
message(STATUS CMAKE_CXX_FLAGS)

add_executable(Tree ${SRC_LIST_C})
