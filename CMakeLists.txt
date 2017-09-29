cmake_minimum_required(VERSION 3.5)

set(TARGET_NAME "logaritmos_tarea1")

project(${TARGET_NAME})
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
add_subdirectory(test)

list(APPEND CMAKE_MODULE_PATH cmake)
set(BOOST_REQUESTED_VERSION 1.61)
