cmake_minimum_required(VERSION 3.8)
project(sim_lamost)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp constant.h convert.h convert.cpp)
add_executable(sim_lamost ${SOURCE_FILES})