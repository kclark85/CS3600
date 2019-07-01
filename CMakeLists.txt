cmake_minimum_required(VERSION 3.14)
project(A3 C)

#sets warnings to be errors
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror")

add_executable(parent parent.c eye2eh.c)
add_executable(child child.c eye2eh.c)
