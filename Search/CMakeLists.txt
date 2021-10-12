cmake_minimum_required(VERSION 3.13)
project(Search)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(${PROJECT_SOURCE_DIR}/ SRC_LIST_C)
include_directories(${PROJECT_SOURCE_DIR}/)


add_executable(Search ${SRC_LIST_C})
