cmake_minimum_required(VERSION 3.7)
project(logaritmos_tarea1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/RTree.cpp src/RTree.h src/SplitHeuristic.cpp src/SplitHeuristic.h src/LinearSplit.cpp src/LinearSplit.h src/GreeneSplit.cpp src/GreeneSplit.h src/Rectangle.cpp src/Rectangle.h)
add_executable(logaritmos_tarea1 ${SOURCE_FILES})