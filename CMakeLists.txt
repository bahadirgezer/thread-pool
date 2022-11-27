cmake_minimum_required(VERSION 3.23)
project(thread_pool)

set(CMAKE_CXX_STANDARD 14)

add_executable(thread_pool src/main.cpp src/operations.cpp src/operations.h)
