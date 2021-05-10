cmake_minimum_required(VERSION 3.19)
project(source)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(source
        ford_falkerson.hpp
        graph.hpp
        main.cpp andrey.cpp)
