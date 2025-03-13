cmake_minimum_required(VERSION 3.15)
project(btl VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(btl src/main.cpp)

target_include_directories(btl PRIVATE include)