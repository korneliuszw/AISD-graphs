cmake_minimum_required(VERSION 3.25)
project(graphy_i_takie_tam)

set(CMAKE_CXX_STANDARD 17)

add_executable(graphy_i_takie_tam main.cpp
        containers.h
        algos.h
        solutions.h
        solutions.cpp "Project1/algos.h" "Project1/containers.h" "Project1/main.cpp" "Project1/solutions.cpp" "Project1/solutions.h")
