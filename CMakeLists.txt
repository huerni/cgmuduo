cmake_minimum_required(VERSION 2.5)

project(cgmuduo)
# 最终编译成so动态库，设置路径为根目录的lib文件夹下面
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 设置调试信息 以及 启动c++17语言标准
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -fPIC")

# 定义参与编译的源代码文件
aux_source_directory(. SRC_LIST)
# 编译生成动态库cgmuduo
add_library(cgmuduo SHARED ${SRC_LIST})