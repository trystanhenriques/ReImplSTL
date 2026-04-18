cmake_minimum_required(VERSION 3.10)

project(ReImplSTL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ReImplSTL
    src/ReImplSTL.cpp
)

target_include_directories(ReImplSTL PRIVATE include)
