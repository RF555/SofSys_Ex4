cmake_minimum_required(VERSION 3.21)
project(SofSys_Ex4 C)

set(CMAKE_C_STANDARD 99)

add_executable(SofSys_Ex4 main.c edges.c edges.h nodes.c nodes.h algo.c algo.h graph.c given_graph.h)
