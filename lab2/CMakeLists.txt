cmake_minimum_required(VERSION 4.0)
project(MyCalcProject CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(calculator STATIC src/calculator.cpp)

add_executable(calc src/main.cpp)

target_link_libraries(calc PRIVATE calculator)

target_include_directories(calc PRIVATE src)
