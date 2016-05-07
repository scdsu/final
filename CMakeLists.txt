cmake_minimum_required(VERSION 3.5)
project(final)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Map.cpp GameObj.cpp Vec3D.cpp Ant.cpp)
add_executable(final ${SOURCE_FILES})