cmake_minimum_required(VERSION 3.10)

project(hello_cmake)
# 设置生成器为 MinGW Makefiles
set(CMAKE_GENERATOR "MinGW Makefiles")

# 设置编译器路径
set(CMAKE_C_COMPILER "C:/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/mingw64/bin/g++.exe")

# 设置 make 工具路径
set(CMAKE_MAKE_PROGRAM "C:/mingw64/bin/mingw32-make.exe")

add_executable(hello_cmake main.c)

