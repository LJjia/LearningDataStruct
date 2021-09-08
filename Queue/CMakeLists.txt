cmake_minimum_required(VERSION 3.13)
project(Queue C)

set(CMAKE_C_STANDARD 99)

aux_source_directory(${PROJECT_SOURCE_DIR}/ SRC_LIST_C)
include_directories(${PROJECT_SOURCE_DIR}/)

add_executable(Queue ${SRC_LIST_C})

