cmake_minimum_required(VERSION 3.10)

project(wangzhe_nongyao VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(wangzhe_nongyao main.cpp user.cpp game.cpp ranking.cpp hero.cpp)