cmake_minimum_required(VERSION 3.10)
# aux这句好像一次只能增加一条路径,因此写两次,两个路径都可以被囊括进去
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST_C)
aux_source_directory(${PROJECT_SOURCE_DIR}/ SRC_LIST_C)
include_directories(${PROJECT_SOURCE_DIR}/inc )

#将hello.cpp生成可执行文件hello
ADD_EXECUTABLE(hello ${SRC_LIST_C})

