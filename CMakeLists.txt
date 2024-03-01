cmake_minimum_required(VERSION 3.12.0)
project(code-challenge-image VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(HEADERS image.h)
set(SOURCES image.cpp main.cpp)

add_executable(code-challenge-image ${HEADERS} ${SOURCES})
