cmake_minimum_required(VERSION 3.5)
project(labyrinth)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(
        SOURCE_FILES
        main.cpp
        Field.cpp
        Field.hpp
        RunnerBase.cpp
        RunnerBase.hpp
        Runner.cpp
        Runner.hpp
        utils.hpp
)

add_executable(labyrinth ${SOURCE_FILES})