cmake_minimum_required(VERSION 4.3.4)
project(TraficSimulator)

set(SRC src/main.cpp)
set(HPP include/main.hpp)

add_executable(${PROJECT_NAME} ${SRC} ${HPP})

target_include_directories(${PROJECT_NAME} PRIVATE include)

