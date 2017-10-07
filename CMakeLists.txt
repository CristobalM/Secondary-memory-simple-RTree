cmake_minimum_required(VERSION 3.5)

set(TARGET_NAME "logaritmos_tarea1")

project(${TARGET_NAME})
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-O3 ")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
#MATH(EXPR stack_size "100 * 1024 * 1024")
#set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,4194304")


list(APPEND CMAKE_MODULE_PATH cmake)
set(BOOST_REQUESTED_VERSION 1.61)


add_subdirectory(src)
add_subdirectory(test)

