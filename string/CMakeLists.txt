cmake_minimum_required(VERSION 3.13)
project(string)

set(CMAKE_CXX_STANDARD 14)
aux_source_directory(${PROJECT_SOURCE_DIR}/ SRC_LIST_C)
include_directories(${PROJECT_SOURCE_DIR}/)

message(${SRC_LIST_C})
add_executable(string ${SRC_LIST_C})
